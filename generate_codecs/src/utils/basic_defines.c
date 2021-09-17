#include <ctype.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils/basic_defines.h"
#include "utils/array.h"
#include "utils/array_of.h"


char * Boolean_to_string(Boolean bool) {
	switch(bool) {
		case false:
			return "false";
		case true:
			return "true";
		default:
			return NULL;
	}
}


char * string_copy(char *string) {
	char *string_copy = (char *)calloc(strlen(string)+1, sizeof(char));
	strcpy(string_copy, string);
	return string_copy;
}

Boolean string_equals(char *string0, char *string1) {
	return (strcmp(string0, string1)==0)? true : false;
}

char * string_to_lower(char *string) {
	size_t string_lower_length = strlen(string);
	char *string_lower = (char *)calloc(string_lower_length+1, sizeof(char));
	for (int i=0; i<string_lower_length; i++) {
		string_lower[i] = tolower(string[i]);
	}
	return string_lower;
}

char * string_to_upper(char *string) {
	size_t string_upper_length = strlen(string);
	char *string_upper = (char *)calloc(string_upper_length+1, sizeof(char));
	for (int i=0; i<string_upper_length; i++) {
		string_upper[i] = toupper(string[i]);
	}
	return string_upper;
}

char * string_make_shortcut(char *string) {
	char *shortcut = (char *)calloc(strlen(string)+1, sizeof(char));
	strcpy(shortcut, string);
	shortcut[0] = tolower(shortcut[0]);
	return shortcut;
}

char * string_appends(char *strings[]) {
	size_t string_length = 0;
	for (int i=0; strings[i]!=NULL; i++) {
		string_length += strlen(strings[i]);
	}
	char *string = (char *)calloc(string_length+1, sizeof(char));
	for (int i=0, string_index=0; strings[i]!=NULL; i++) {
		for (int index=0; index<strlen(strings[i]); string_index++, index++) {
			string[string_index] = strings[i][index];
		}
	}
	return string;
}

char * string_random(size_t string_length_min, size_t string_length_max) {
	size_t string_printable_length = 96;
	char *string_printable = "0123456789qwertyuiopasdfgghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM`~!@#$%%^&*()-_=+[{]}\\|;:\'\",<.>/?";
	size_t string_length = string_length_min + random()%(string_length_max+1-string_length_min);
	char *string = (char *)calloc(string_length+1, sizeof(char));
	for (int i=0; i<string_length; i++) {
		string[i] = string_printable[random() % string_printable_length];
	}
	return string;
}


void file_write(char *file_path, char *source_code) {
	FILE *file_stream = fopen(file_path, "w");
	fprintf(file_stream, "%s", source_code);
	{
		fclose(file_stream);
	}
}

char * file_read(char *file_path) {
	char *string;
	{
		size_t string_length;
		FILE *string_stream = open_memstream(&string, &string_length);
		FILE *file_stream = NULL;
		if ((file_stream = fopen(file_path, "r"))==NULL) {
			error("open file in \'file_read\' function");
		}
		ssize_t read;
		char *line = NULL;
		size_t line_length = 0;
		while ((read = getline(&line, &line_length, file_stream)) != -1) {
			fprintf(string_stream, "%s", line);
			{
				free(line);
				line = NULL;
			}
		}
		{
			fclose(string_stream);
			fclose(file_stream);
			free(line);
		}
	}
	return string;
}

char * file_get_directory_path(char *file_path) {
	ssize_t directory_path_length;
	for (directory_path_length=strlen(file_path)-1; directory_path_length>=0; directory_path_length--) {
		if (file_path[directory_path_length] == '/') {
			break;
		}
	}
	if (directory_path_length==-1) {
		return NULL;
	}
	char *directory_path = (char *)calloc(directory_path_length+1, sizeof(char));
	strncpy(directory_path, file_path, directory_path_length);
	return directory_path;
}

Array * directory_path_scan_for_h_files(char *directory_path) {
	Array *h_files = Array_of_string_create();
	DIR *directory;
	struct dirent *file;
	if ((directory = opendir(directory_path)) != NULL) {
		while((file = readdir(directory)) != NULL) {
			if (
				!string_equals(file->d_name, ".") &&
				!string_equals(file->d_name, "..") &&
				file->d_name[strlen(file->d_name)-1]=='h'
			) {
				Array_add(h_files, file->d_name);
			}
		}
		closedir(directory);
	}
	return h_files;
}
