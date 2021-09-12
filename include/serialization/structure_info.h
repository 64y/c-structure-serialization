#ifndef STRUCTURE_INFO_H
#define STRUCTURE_INFO_H

#include <stdio.h>


#define PATH_SOURCES "src"
#define PATH_LIBRARIES "lib"

#define PATH_SHARED_LIBRARY "lib/library"
#define PATH_SHARED_LIBRARY_SOURCE_FILES "lib/library.source"

#define PATH_INCLUDES_H "src/includes.h"
#define PATH_ALL_INCLUDED_H "src/utils/all_included.h"
#define	PATH_ALL_INCLUDED_C	"src/utils/all_included.c"


typedef struct StructureInfo {
		
	char *name;
	char *name_lower;
	char *name_upper;
	
	char *to_string_name;
	char *json_encode_name;
	char *json_decode_name;
	
	char *file_name;
	char *path_structure_h;
	char *path_structure_serialize_h;
	char *path_structure_serialize_c;
	
	size_t all_strings_size;
	char **all_strings;
} StructureInfo;

StructureInfo * StructureInfo_create(char *structure_name, char *structure_file_name);
StructureInfo * StructureInfo_create_by_name(char *structure_name);
void StructureInfo_free(StructureInfo *structureInfo);
char * StructureInfo_to_string(StructureInfo *structureInfo);

void StructureInfo_create_sources(StructureInfo *structureInfo);

void compile_shared_library();

#endif
