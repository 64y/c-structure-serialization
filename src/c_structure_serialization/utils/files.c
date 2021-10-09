#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_structure_serialization/utils/boolean.h"
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
