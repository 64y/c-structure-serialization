#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include <openssl/md5.h>

#include "c_structure_serialization/serializer.h"


char * file_md5_hex(char *file_name);
char * file_time_of_last_modification(char *file_name);
char * program_library_path();

char * get_serializer_method_name(char *structure_name, char *method_name);


Serializer * Serializer_create(char *structure_name) {
	Serializer *serializer = (Serializer *)malloc(sizeof(Serializer));
	char *library_path = program_library_path();
	serializer->handle = dlopen(library_path, RTLD_NOW|RTLD_GLOBAL);
	if (!serializer->handle) {
		fprintf(stderr, "\'Serializer_create\' method is not able to open \"%s\" library!\n", library_path);
		exit(0);
	}
	char *method_name_to_string = get_serializer_method_name(structure_name, "to_string");
	*(void **) (&serializer->to_string) = dlsym(serializer->handle, method_name_to_string);
	if (dlerror()) {
		fprintf(stderr, "\'Serializer_create\' method can\'t load \'%s\' from \"%s\" library!\n", method_name_to_string, library_path);
		exit(0);
	}
	char *method_name_json_encode = get_serializer_method_name(structure_name, "json_encode");
	*(void **) (&serializer->json_encode) = dlsym(serializer->handle, method_name_json_encode);
	if (dlerror()) {
		fprintf(stderr, "\'Serializer_create\' method can\'t load \'%s\' from \"%s\" library!\n", method_name_json_encode, library_path);
		exit(0);
	}
	char *method_name_json_decode = get_serializer_method_name(structure_name, "json_decode");
	*(void **) (&serializer->json_decode) = dlsym(serializer->handle, method_name_json_decode);
	if (dlerror()) {
		fprintf(stderr, "\'Serializer_create\' method can\'t load \'%s\' from \"%s\" library!\n", method_name_json_decode, library_path);
		exit(0);
	}
	{
		free(library_path);
		free(method_name_to_string);
		free(method_name_json_encode);
		free(method_name_json_decode);
	}
	return serializer;
}

void Serializer_free(Serializer *serializer) {
	if (serializer != NULL) {
		if (serializer->handle != NULL) {
			dlclose(serializer->handle);
			serializer->handle = NULL;
		}
		serializer->to_string = NULL;
		serializer->json_encode = NULL;
		serializer->json_decode = NULL;
		free(serializer);
		serializer = NULL;
	}
}


char * file_md5_hex(char *file_name) {
	unsigned char *md5_hash_bin = (unsigned char *)calloc(MD5_DIGEST_LENGTH+1, sizeof(unsigned char));
	{
		MD5_CTX md5_ctx;
		MD5_Init(&md5_ctx);
		size_t buff_length = 2048, read=0;
		unsigned char *buff = (unsigned char *)calloc(buff_length, sizeof(unsigned char));
		FILE *f = fopen(file_name, "rb");
		while (1) {
			read = fread(buff, sizeof(unsigned char), buff_length, f);
			if (read==0) {
				break;
			}
			MD5_Update(&md5_ctx, buff, read);
		}
		fclose(f);
		MD5_Final(md5_hash_bin, &md5_ctx);
		{
			free(buff);
		}
	}
	char *md5_hash_hex;
	{
		size_t md5_hash_hex_length;
		FILE *md5_hash_hex_stream = open_memstream(&md5_hash_hex, &md5_hash_hex_length);
		for (int i=0; i<MD5_DIGEST_LENGTH; i++) {
			fprintf(md5_hash_hex_stream, "%02x", md5_hash_bin[i]);
		}
		fclose(md5_hash_hex_stream);
	}
	{
		free(md5_hash_bin);
	}
	return md5_hash_hex;
}

char * file_time_of_last_modification(char *file_name) {
	size_t file_time_length = 4 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1;
	char *file_time = (char *)calloc(file_time_length, sizeof(char));
	{
		struct stat *file_statistic = (struct stat *)malloc(sizeof(struct stat));
		stat(file_name, file_statistic);
		struct tm *time_modification = gmtime(&file_statistic->st_mtime);
		strftime(file_time, file_time_length, "%F_%T", time_modification);
		{
			free(file_statistic);
			time_modification = NULL;
		}
	}
	return file_time;
}

char * program_library_path() {
	char *library_path;
	{
		char *file_path_current = getenv("_");
		char *last_slash = strrchr(file_path_current, '/');
		char *file_path;
		{
			size_t file_path_length = (last_slash==NULL) ? 0 : strlen(file_path_current) - (strlen(last_slash)-1);
			file_path = (char *)calloc(file_path_length+1, sizeof(char));
			strncpy(file_path, file_path_current, file_path_length);
		}
		char *file_name;
		{
			char *file_name_source;
			size_t file_name_length;
			if (last_slash==NULL) {
				file_name_source = file_path_current;
				file_name_length = strlen(file_path_current);
			} else {
				file_name_source = last_slash+1;
				file_name_length = strlen(last_slash)-1;
			}
			file_name = (char *)calloc(file_name_length+1, sizeof(char));
			strncpy(file_name, file_name_source, file_name_length);
		}
		char *file_md5 = file_md5_hex(file_path_current);
		char *modification_time = file_time_of_last_modification(file_path_current);
		size_t library_path_length;
		FILE *library_path_stream = open_memstream(&library_path, &library_path_length);
		fprintf(library_path_stream, "%s%s.%s.%s.%s", file_path, LIBRARY_NAME, file_name, file_md5, modification_time);
		fclose(library_path_stream);
		{
			free(file_path);
			free(file_name);
			free(file_md5);
			free(modification_time);
		}
	}
	return library_path;
}

char * get_serializer_method_name(char *structure_name, char *method_name) {
	char *serializer_method_name;
	{
		size_t serializer_method_name_length;
		FILE *serializer_method_name_stream = open_memstream(&serializer_method_name, &serializer_method_name_length);
		fprintf(serializer_method_name_stream, "%s_%s", structure_name, method_name);
		fclose(serializer_method_name_stream);
	}
	return serializer_method_name;
}
