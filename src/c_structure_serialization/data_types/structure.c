#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_structure_serialization/utils/array.h"
#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/data_types/attribute_type.h"
#include "c_structure_serialization/data_types/basic_type.h"
#include "c_structure_serialization/data_types/dimension.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/data_types/structure_regular_expressions.h"


Structure * Structure_create_by_file_path_and_name(char *file_path, char *name) {
	Structure *structure = (Structure *)malloc(sizeof(Structure));
	structure->file_path = string_copy(file_path);
	structure->name = string_copy(name);
	structure->name_lower = string_to_lower(structure->name);
	structure->name_upper = string_to_upper(structure->name);
	structure->shortcut = string_make_shortcut(structure->name);
	structure->size = 0;
	structure->head = NULL;
	return structure;
}

Structure * Structure_create_by_file_path_and_source_code(char *file_path, Array *source_code) {
	Structure *structure = (Structure *)malloc(sizeof(Structure));
	structure->file_path = string_copy(file_path);
	char *structure_name, *structure_struct_name;
	{
		char **matches;
		matches = RegularExpression_parse(structureRegularExpressions->structureStart, (char *)Array_get(source_code, 0));
		char *structure_name_typedef = matches[0];
		char *structure_name_first = matches[1];
		{
			free(matches);
		}
		matches = RegularExpression_parse(structureRegularExpressions->structureEnd, (char *)Array_get(source_code, Array_size(source_code)-1));
		char *structure_name_second = matches[0];
		{
			free(matches);
		}
		if (string_equals(structure_name_typedef, "typedef ") && (strlen(structure_name_first)>strlen(structure_name_second)) && (strlen(structure_name_second)>0)) {
			structure_name = string_copy(structure_name_second);
		} else if (string_equals(structure_name_typedef, "") && (strlen(structure_name_first)>0) && string_equals(structure_name_second, "")) {
			structure_name = string_copy(structure_name_first);
		} else {
			char *source_code_string = Array_to_string(source_code);
			fprintf(stderr, "\'Structure_create_by_file_path_and_source_code\' method can\'t create Structure from source code:%s\n", source_code_string);
			exit(1);
		}
		structure_struct_name = string_copy(structure_name_first);
		{
			string_free(structure_name_typedef);
			string_free(structure_name_first);
			string_free(structure_name_second);
		}
	}
	structure->name = structure_name;
	structure->name_lower = string_to_lower(structure->name);
	structure->name_upper = string_to_upper(structure->name);
	structure->shortcut = string_make_shortcut(structure->name);
	structure->size = 0;
	structure->head = NULL;
	{
		for (int i=1; i<Array_size(source_code)-1; i++) {
			size_t num_matches = structureRegularExpressions->attribute->num_matches;
			char **matches = RegularExpression_parse(structureRegularExpressions->attribute, (char *)Array_get(source_code, i));
			
			AttributeType type;
			char *attribute_data_type = matches[0];
			if (string_equals(structure_struct_name, attribute_data_type) && !string_equals(structure_struct_name, structure->name)) {
				attribute_data_type = structure->name;
			}
			char *attribute_dynamic_sizes_string = matches[1];
			size_t attribute_dynamic_sizes=0;
			{
				for (int string_i=0; string_i<strlen(attribute_dynamic_sizes_string); string_i++) {
					if (attribute_dynamic_sizes_string[string_i]=='*') {
						attribute_dynamic_sizes = attribute_dynamic_sizes+1;
					}
				}
			}
			char *attribute_name = matches[2];
			char *attribute_static_sizes_string = matches[3];
			size_t attribute_static_sizes=0;
			{
				for (int string_i=0; string_i<strlen(attribute_static_sizes_string); string_i++) {
					if (attribute_static_sizes_string[string_i]=='[') {
						attribute_static_sizes = attribute_static_sizes+1;
					}
				}
			}
			size_t attribute_sizes_names = 0;
			{
				for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
					if (strlen(attribute_name)<strlen(curr->name) && strncmp(attribute_name, curr->name, strlen(attribute_name))==0) {
						attribute_sizes_names = attribute_sizes_names+1;
					}
				}
			}

			bool attribute_is_primitive = (BasicType_get_by_name(attribute_data_type)!=NULL)?true:false;
			bool attribute_is_char = string_equals(attribute_data_type, "char");
			
			if (
				attribute_static_sizes==0 && attribute_dynamic_sizes==0
			) {
				type = (attribute_is_primitive)?PRIMITIVE:STRUCTURE;
			} else if (
				attribute_is_char && (attribute_static_sizes+attribute_dynamic_sizes==1) && (attribute_sizes_names==0)
			) {
				type = STRING;
				attribute_data_type = "char *";
				attribute_static_sizes = 0;
				attribute_dynamic_sizes = 0;
			} else if (
				!attribute_is_primitive && attribute_static_sizes==0 && attribute_dynamic_sizes==1 && attribute_sizes_names==0
			) {
				type = STRUCTURE_POINTER;
				attribute_dynamic_sizes = attribute_dynamic_sizes-1;
			} else if (
				(attribute_static_sizes>0 && attribute_dynamic_sizes==0 && attribute_sizes_names==0) ||
				(attribute_static_sizes>0 && attribute_dynamic_sizes==0 && attribute_sizes_names==attribute_static_sizes) ||
				(attribute_static_sizes==0 && attribute_dynamic_sizes>0 && attribute_sizes_names==attribute_dynamic_sizes) ||
				(attribute_static_sizes>0 && attribute_dynamic_sizes>0 && attribute_sizes_names==attribute_dynamic_sizes) ||
				(attribute_static_sizes>0 && attribute_dynamic_sizes>0 && attribute_sizes_names==attribute_static_sizes+attribute_dynamic_sizes)
			) {
				type = (attribute_is_primitive) ? PRIMITIVE_ARRAY : STRUCTURE_ARRAY;
			} else if (
				(attribute_static_sizes==0 && attribute_dynamic_sizes>0 && attribute_sizes_names==attribute_dynamic_sizes-1) ||
				(attribute_static_sizes>0 && attribute_dynamic_sizes>0 && attribute_sizes_names==attribute_dynamic_sizes-1) ||
				(attribute_static_sizes>0 && attribute_dynamic_sizes>0 && attribute_sizes_names==attribute_static_sizes+attribute_dynamic_sizes-1)
			) {
				if (attribute_is_char) {
					type = STRING_ARRAY;
					attribute_data_type = "char *";					
				} else if (!attribute_is_primitive) {
					type = STRUCTURE_POINTER_ARRAY;
				} else {
					type = NO_TYPE;
				}
				attribute_dynamic_sizes = attribute_dynamic_sizes-1;
			} else if (
				attribute_is_char && attribute_static_sizes>0 && attribute_dynamic_sizes==0 && attribute_sizes_names==attribute_static_sizes-1
			) {
				type = STRING_ARRAY;
				attribute_data_type = "char *";
				attribute_static_sizes = attribute_static_sizes-1;
			} else {
				type = NO_TYPE;
			}
			if (type == NO_TYPE) {
				fprintf(stderr, "\'Structure_create_by_file_path_and_source_code\' method can\'t determine \'%s\' type!", (char *) Array_get(source_code, i));
				exit(1);
			}
			Dimension *dimension;
			if (attribute_static_sizes+attribute_dynamic_sizes>=1) {
				dimension = Dimension_create(attribute_static_sizes, attribute_dynamic_sizes);
				if (attribute_static_sizes>0) {
					char *buff = (char *)calloc(32, sizeof(char));
					for (int attribute_static_index=0, string_start=0; attribute_static_index<attribute_static_sizes; attribute_static_index++) {
						sscanf(attribute_static_sizes_string+string_start, "[%[^]]s]", buff);
						string_start += 1+strlen(buff)+1;
						Dimension_set_dimension(dimension, attribute_static_index, buff);
					}
					{
						string_free(buff);
					}
				}
				int index=((attribute_static_sizes>0 && attribute_dynamic_sizes==0 && attribute_sizes_names==attribute_static_sizes)||(attribute_static_sizes>0 && attribute_dynamic_sizes>0 && attribute_sizes_names==attribute_static_sizes+attribute_dynamic_sizes))?0:attribute_static_sizes;
				for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
					if (strlen(attribute_name)<strlen(curr->name) && strncmp(attribute_name, curr->name, strlen(attribute_name))==0) {
						Dimension_set_dimension(dimension, index, curr->name);
						index = index + 1;
					}
				}
				if ((attribute_static_sizes+attribute_dynamic_sizes)==attribute_sizes_names) {
					dimension->static_size = 0;
					dimension->dynamic_size = attribute_static_sizes+attribute_dynamic_sizes;
				}
				for (int j=dimension->static_size; j<dimension->size; j++) {
					char *dimension_old = dimension->dimensions[j];
					char *dimension_new = string_appends(structure->shortcut, "->", dimension_old, NO_MORE_STRINGS);
					Dimension_set_dimension(dimension, j, dimension_new);
					{
						dimension_old = NULL;
						string_free(dimension_new);
					}
				}
			} else {
				dimension = NULL;
			}
			
			Attribute *attribute = Attribute_create(type, attribute_data_type, attribute_name, dimension);
			Structure_add(structure, attribute);			
			
			{
				attribute_data_type = NULL;
				attribute_dynamic_sizes_string = NULL;
				attribute_name = NULL;
				attribute_static_sizes_string = NULL;
				for (int matches_i=0; matches_i<num_matches; matches_i++) {
					if (matches[matches_i]!=NULL) {
						string_free(matches[matches_i]);
					}
				}
				free(matches);
				matches = NULL;
			}
		}
	}
	{
		string_free(structure_struct_name);
	}
	return structure;
}

void Structure_free(Structure *structure) {
	if (structure!=NULL) {
		if (structure->file_path!=NULL) {
			string_free(structure->file_path);
		}
		if (structure->name!=NULL) {
			string_free(structure->name);
		}
		if (structure->name_lower!=NULL) {
			string_free(structure->name_lower);
		}
		if (structure->name_upper!=NULL) {
			string_free(structure->name_upper);
		}
		if (structure->shortcut!=NULL) {
			string_free(structure->shortcut);
		}
		for (Attribute *curr=structure->head; structure->head!=NULL; curr=structure->head) {
			structure->head = structure->head->next;
			Attribute_free(curr);
		}
		free(structure);
		structure = NULL;
	}
}

char * Structure_to_string(Structure *structure) {
	char *structure_string;
	{
		size_t structure_string_length;
		FILE *structure_string_stream = open_memstream(&structure_string, &structure_string_length);
		fprintf(
			structure_string_stream,
			"Structure@%lX\n"
			"file path: \'%s\';\n"
			"name: \'%s\';\n"
			"name_lower: \'%s\';\n"
			"name_upper: \'%s\';\n"
			"shortcut: \'%s\';\n"
			"size: \'%ld\';\n"
			"head: \'Attribute@%lX\'",
			(long)(void *)structure, structure->file_path, structure->name, structure->name_lower, structure->name_upper, structure->shortcut, structure->size, (long)(void *)structure->head
		);
		for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
			char *attribute_string = Attribute_to_string(curr);
			fprintf(structure_string_stream, "\n|_ %s", attribute_string);
			string_free(attribute_string);
		}
		fprintf(structure_string_stream, "\n");
		fclose(structure_string_stream);
	}
	return structure_string;
}


void Structure_add(Structure *structure, Attribute *attribute) {
	if (structure->head==NULL) {
		structure->size = 1;
		structure->head = attribute;
	} else {
		Attribute *curr = structure->head;
		while (curr->next!=NULL) {
			curr = curr->next;
		}
		structure->size = structure->size + 1;
		curr->next = attribute;
	}
}

bool Structure_delete(Structure *structure, Attribute *attribute) {
	if (structure->head==NULL || attribute==NULL) {
		return false;
	}
	if (structure->head==attribute) {
		Attribute *curr = structure->head;
		structure->head = structure->head->next;
		curr->next = NULL;
		Attribute_free(curr);
		structure->size = structure->size - 1;
		return true;
	} else {
		for (Attribute *prev = structure->head, *curr=structure->head->next; prev!=NULL && curr!=NULL; prev=prev->next, curr=curr->next) {
			if (curr==attribute) {
				prev->next = curr->next;
				curr->next = NULL;
				Attribute_free(curr);
				structure->size = structure->size - 1;
				break;
			}
		}
		return true;
	}
	return false;
}

bool Structure_contains_string_attributes(Structure *structure) {
	bool does = false;
	for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
		does |= curr->type==STRING || curr->type==STRING_ARRAY;
	}
	return does;
}

bool Structure_contains_array_attributes(Structure *structure) {
	bool does = false;
	for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
		does |= curr->type==PRIMITIVE_ARRAY || curr->type==STRING_ARRAY || curr->type==STRUCTURE_ARRAY || curr->type==STRUCTURE_POINTER_ARRAY;
	}
	return does;
}

bool Structure_contains_structure_attributes(Structure *structure) {
	bool does = false;
	for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
		does |= curr->type==STRUCTURE || curr->type==STRUCTURE_POINTER || curr->type==STRUCTURE_ARRAY || curr->type==STRUCTURE_POINTER_ARRAY;
	}
	return does;
}


void * array_Structure_create_pack_arguments(char *file_path, Array *source_code) {
	void **args = (void **)calloc(2, sizeof(void *));
	args[0] = file_path;
	args[1] = source_code;
	return args;
}

void * array_Structure_create(void *element) {
	void **args = (void **) element;
	Structure *structure = Structure_create_by_file_path_and_source_code((char *)args[0], (Array *) args[1]);
	free(args);
	return structure;
}

void array_Structure_free(void *element) {
	Structure_free((Structure *) element);
}

char * array_Structure_to_string(void *element) {
	return Structure_to_string((Structure *) element);
}

Array * Array_create_for_Structure() {
	return Array_create(array_Structure_create, array_Structure_free, array_Structure_to_string);
}

