#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_structure_serialization/utils/array.h"
#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/utils/files.h"


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
		if ((file_stream=fopen(file_path, "r"))==NULL) {
			fprintf(stderr, "\'file_read\' method can\'t read file \"%s\"!\n", file_path);
			exit(1);
		}
		ssize_t read;
		char *line = NULL;
		size_t line_length = 0;
		while ((read = getline(&line, &line_length, file_stream))!=-1) {
			fprintf(string_stream, "%s", line);
		}
		{
			fclose(string_stream);
			fclose(file_stream);
			string_free(line);
		}
	}
	return string;
}

char * file_get_directory_path(char *file_path) {
	ssize_t directory_path_length;
	for (directory_path_length=strlen(file_path)-1; directory_path_length>=0; directory_path_length--) {
		if (file_path[directory_path_length]=='/') {
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
	Array *h_files = Array_create_for_string();
	{
		Array *directories = Array_create_for_string();
		Array_add(directories, directory_path);
		for (int i=0; i<Array_size(directories); i++) {
			char *curr_directory_path = (char *) Array_get(directories, i);
			DIR *directory;
			struct dirent *file;
			
			if ((directory = opendir(curr_directory_path)) != NULL) {
				while((file = readdir(directory)) != NULL) {
					switch (file->d_type) {
						case DT_DIR: {
							if (string_equals(".", file->d_name) || string_equals("..", file->d_name)) {
								break;
							}
							char *path_name = string_appends(curr_directory_path, "/", file->d_name, NO_MORE_STRINGS);
							Array_add(directories, path_name);
							{
								string_free(path_name);
							}
							break;
						}
						case DT_REG: {
							if (string_ends_with(file->d_name, ".h")) {
								char *file_name = string_appends(curr_directory_path, "/", file->d_name, NO_MORE_STRINGS);
								Array_add(h_files, file_name);
								{
									string_free(file_name);
								}
							}
							break;
						}
						default: {
							fprintf(stderr, "In \'directory_path_scan_for_h_files\' can\'t work with file \'%s\' of type \'%d\'!", file->d_name, file->d_type);
						}
					}
				}
				closedir(directory);
			}
		}
		{
			Array_free(directories);
		}
	}
	Array_sort(h_files, array_string_cmp);
	return h_files;
}
