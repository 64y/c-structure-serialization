#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "utils/basic_defines.h"
#include "serialization/structure_info.h"


StructureInfo * StructureInfo_create(char *structure_name, char *structure_file_name) {
	StructureInfo *structureInfo = (StructureInfo *)malloc(sizeof(StructureInfo));
	
	structureInfo->name = string_copy(structure_name);
	structureInfo->name_lower = string_to_lower(structureInfo->name);
	structureInfo->name_upper = string_to_upper(structureInfo->name);
	
	structureInfo->to_string_name = string_appends((char *[]){structureInfo->name, "_", "to_string", NULL});
	structureInfo->json_encode_name = string_appends((char *[]){structureInfo->name, "_", "json_encode", NULL});
	structureInfo->json_decode_name = string_appends((char *[]){structureInfo->name, "_", "json_decode", NULL});
	
	structureInfo->file_name = string_copy(structure_file_name);
	structureInfo->path_structure_h = string_appends((char *[]){PATH_SOURCES, "/", structureInfo->file_name, NULL});
	structureInfo->path_structure_serialize_h = string_appends((char *[]){PATH_SOURCES, "/", "libraries", "/", structureInfo->name_lower, "_", "library.h", NULL});
	structureInfo->path_structure_serialize_c = string_appends((char *[]){PATH_SOURCES, "/", "libraries", "/", structureInfo->name_lower, "_", "library.c", NULL});
	
	structureInfo->all_strings_size = 10;
	structureInfo->all_strings = (char **)calloc(structureInfo->all_strings_size, sizeof(char *));
	structureInfo->all_strings[0] = structureInfo->name;
	structureInfo->all_strings[1] = structureInfo->name_lower;
	structureInfo->all_strings[2] = structureInfo->name_upper;
	structureInfo->all_strings[3] = structureInfo->to_string_name;
	structureInfo->all_strings[4] = structureInfo->json_encode_name;
	structureInfo->all_strings[5] = structureInfo->json_decode_name;
	structureInfo->all_strings[6] = structureInfo->file_name;
	structureInfo->all_strings[7] = structureInfo->path_structure_h;
	structureInfo->all_strings[8] = structureInfo->path_structure_serialize_h;
	structureInfo->all_strings[9] = structureInfo->path_structure_serialize_c;
	StructureInfo_create_sources(structureInfo);
	return structureInfo;
}

StructureInfo * StructureInfo_create_by_name(char *structure_name) {
	StructureInfo *structureInfo = (StructureInfo *)malloc(sizeof(StructureInfo));
	structureInfo->name = string_copy(structure_name);
	structureInfo->name_lower = string_to_lower(structureInfo->name);
	structureInfo->to_string_name = string_appends((char *[]){structureInfo->name, "_", "to_string", NULL});
	structureInfo->json_encode_name = string_appends((char *[]){structureInfo->name, "_", "json_encode", NULL});
	structureInfo->json_decode_name = string_appends((char *[]){structureInfo->name, "_", "json_decode", NULL});
	structureInfo->all_strings_size = 5;
	structureInfo->all_strings = (char **)calloc(structureInfo->all_strings_size, sizeof(char *));
	structureInfo->all_strings[0] = structureInfo->name;
	structureInfo->all_strings[1] = structureInfo->name_lower;
	structureInfo->all_strings[2] = structureInfo->to_string_name;
	structureInfo->all_strings[3] = structureInfo->json_encode_name;
	structureInfo->all_strings[4] = structureInfo->json_decode_name;
	StructureInfo_create_sources(structureInfo);
	return structureInfo;
}


void StructureInfo_free(StructureInfo *structureInfo) {
	if (structureInfo != NULL) {
		for (int i=0; i<structureInfo->all_strings_size; i++) {
			if (structureInfo->all_strings[i] == NULL) {
				continue;
			} else {
				free(structureInfo->all_strings[i]);
				structureInfo->all_strings[i] = NULL;
			}
		}
		free(structureInfo->all_strings);
		structureInfo->all_strings = NULL;
		free(structureInfo);
		structureInfo = NULL;
	}
}

char * StructureInfo_to_string(StructureInfo *structureInfo) {
	char *structureInfo_string;
	{
		size_t structureInfo_string_length;
		FILE *structureInfo_string_stream = open_memstream(&structureInfo_string, &structureInfo_string_length);
		fprintf(structureInfo_string_stream, "StructureInfo:\n");
		for (int i=0; i<structureInfo->all_strings_size; i++) {
			fprintf(structureInfo_string_stream, "%s\n", structureInfo->all_strings[i]);
		}
		fclose(structureInfo_string_stream);
	}
	return structureInfo_string;
}

void StructureInfo_create_sources(StructureInfo *structureInfo) {
	if (access(PATH_SOURCES, F_OK) != 0) {
		mkdir(PATH_SOURCES, 0700);
	}
	if (access(PATH_LIBRARIES, F_OK) != 0) {
		mkdir(PATH_LIBRARIES, 0700);
	}
	if (access("src/libraries", F_OK) != 0) {
		mkdir("src/libraries", 0700);
	}
	if (access(PATH_SHARED_LIBRARY_SOURCE_FILES, F_OK) != 0) {
		file_write(PATH_SHARED_LIBRARY_SOURCE_FILES, "EMPTY");
	}
	if (access("src/utils", F_OK) != 0) {
		mkdir("src/utils", 0700);
	}
}

void compile_shared_library() {
	char *source_files_previous = file_read(PATH_SHARED_LIBRARY_SOURCE_FILES);
	{
		size_t source_files_current_command_length;
		char *source_files_current_command;
		FILE *source_files_current_command_stream = open_memstream(&source_files_current_command, &source_files_current_command_length);
		fprintf(
			source_files_current_command_stream, 
			"find %s -type f \\( -name \"*.h\" -o -name \"*.c\" \\) -print > %s",
			PATH_SOURCES, PATH_SHARED_LIBRARY_SOURCE_FILES
		);
		fclose(source_files_current_command_stream);
		system(source_files_current_command);
		free(source_files_current_command);
	}
	char *source_files_current = file_read(PATH_SHARED_LIBRARY_SOURCE_FILES);	
	if (string_equals(source_files_previous, source_files_current)) {
		free(source_files_previous);
		free(source_files_current);
		return;
	} else {
		free(source_files_previous);
		free(source_files_current);
	}
	size_t command_length;
	char *command;
	FILE *command_stream = open_memstream(&command, &command_length);
	fprintf(
		command_stream,
		"gcc "
		"-shared -nostartfiles "
		"-I %s "
		"-o %s "
		"$(find %s -type f -name *.c)",
		PATH_SOURCES, PATH_SHARED_LIBRARY, PATH_SOURCES
	);
	fclose(command_stream);
	system(command);
	free(command);
}
