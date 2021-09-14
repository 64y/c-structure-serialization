#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "utils/basic_defines.h"
#include "data_types/structures_regular_expressions.h"


RegularExpression * RegularExpression_create(char *pattern, size_t num_matches) {
	RegularExpression *regularExpression = (RegularExpression *)malloc(sizeof(RegularExpression));
	regularExpression->pattern = string_copy(pattern);
	regularExpression->num_matches = num_matches;
	regularExpression->re = (regex_t *)malloc(sizeof(regex_t));
	if (regcomp(regularExpression->re, regularExpression->pattern, REG_EXTENDED) != 0) {
		error("compile \'regex_t\' pattern for \'RegularExpression\' structure");
		return NULL;
	}
	return regularExpression;
}

void RegularExpression_free(RegularExpression *regularExpression) {
	if (regularExpression!= NULL) {
		if (regularExpression->pattern != NULL) {
			free(regularExpression->pattern);
			regularExpression->pattern = NULL;
		}
		regularExpression->num_matches = 0;
		if (regularExpression->re != NULL) {
			regfree(regularExpression->re);
			free(regularExpression->re);
			regularExpression->re = NULL;
		}
		free(regularExpression);
		regularExpression = NULL;
	}
}

char * RegularExpression_to_string(RegularExpression *regularExpression) {
	char *regularExpression_string;
	{
		size_t regularExpression_string_length;
		FILE *regularExpression_string_out = open_memstream(&regularExpression_string, &regularExpression_string_length);
		fprintf(regularExpression_string_out, "RegularExpression:\npattern: \'%s\', num match: \'%ld\'", regularExpression->pattern, regularExpression->num_matches);
		fclose(regularExpression_string_out);
	}
	return regularExpression_string;
}

Boolean RegularExpression_match(RegularExpression *regularExpression, char *string) {
	return (regexec(regularExpression->re, string, 0, NULL, 0) == 0) ? true : false;
}

char ** RegularExpression_parse(RegularExpression *regularExpression, char *string) {
	char **matches;
	int result;
	size_t nmatch = regularExpression->num_matches+1;
	regmatch_t *pmatch = (regmatch_t *)calloc(nmatch, sizeof(regmatch_t));
	if ((result = regexec(regularExpression->re, string, nmatch, pmatch, 0)) == 0) {
		matches = (char **)calloc(regularExpression->num_matches, sizeof(char *));
		for (int i=0; i<regularExpression->num_matches; i++) {
			size_t match_length;
			FILE *match_stream = open_memstream(&matches[i], &match_length);
			fprintf(match_stream, "%.*s", pmatch[1+i].rm_eo-pmatch[1+i].rm_so, &string[pmatch[1+i].rm_so]);
			fclose(match_stream);
		}
	} else {
			matches = NULL;
	}
	free(pmatch);
	return matches;
}


RegularExpressions * RegularExpressions_create(char *struct_name) {
	RegularExpressions *regularExpressions = (RegularExpressions *)malloc(sizeof(RegularExpressions));
	
	regularExpressions->attribute.primitive = RegularExpression_create("^\t(char|unsigned\\schar|byte|short|int|long|float|double)\\s([0-9a-zA-Z_]+);", 2);
	regularExpressions->attribute.structure = RegularExpression_create("([0-9a-zA-Z_]+)\\s([0-9a-zA-Z_]+);", 2);
	regularExpressions->attribute.primitive_array_0 = RegularExpression_create("^\t(char|unsigned\\schar|byte|short|int|long|float|double)\\s*(\\*+)+\\s*([0-9a-zA-Z_]+);", 3);
	regularExpressions->attribute.primitive_array_1 = RegularExpression_create("^\t(char|unsigned\\schar|byte|short|int|long|float|double)\\s([0-9a-zA-Z_]+)((\\[[0-9]+\\])+);", 3);
	regularExpressions->attribute.primitive_array_2 = RegularExpression_create("^\t(char|unsigned\\schar|byte|short|int|long|float|double)\\s*(\\*+)+\\s*([0-9a-zA-Z_]+)((\\[[0-9]+\\])+);", 4);
	regularExpressions->attribute.structure_pointer_array_0 = RegularExpression_create("([0-9a-zA-Z_]+)\\s*(\\*+)+\\s*([0-9a-zA-Z_]+);", 3);
	regularExpressions->attribute.structure_array_1 = RegularExpression_create("([0-9a-zA-Z_]+)\\s([0-9a-zA-Z_]+)((\\[[0-9]+\\])+)", 3);
	regularExpressions->attribute.structure_pointer_array_2 = RegularExpression_create("([0-9a-zA-Z_]+)\\s*(\\*+)+\\s*([0-9a-zA-Z_]+)((\\[[0-9]+\\])+);", 4);
	
	char *pattern_structure_start;
	{
		size_t pattern_structure_start_length;
		FILE *pattern_structure_start_stream = open_memstream(&pattern_structure_start, &pattern_structure_start_length);
		fprintf(pattern_structure_start_stream, "(typedef\\s)?(struct\\s%s)(\\s)?(\\{)", struct_name);
		fclose(pattern_structure_start_stream);
	}
	regularExpressions->structure.start = RegularExpression_create(pattern_structure_start, 0);
	
	char *pattern_structure_end;
	{
		size_t pattern_structure_end_length;
		FILE *pattern_structure_end_stream = open_memstream(&pattern_structure_end, &pattern_structure_end_length);
		fprintf(pattern_structure_end_stream, "(\\})(\\s)?(%s)?(\\s)?(;)", struct_name);
		fclose(pattern_structure_end_stream);
	}
	regularExpressions->structure.end = RegularExpression_create(pattern_structure_end, 0);
	
	{
		free(pattern_structure_start);
		free(pattern_structure_end);
	}
	return regularExpressions;
}

void RegularExpressions_free(RegularExpressions *regularExpressions) {
	if (regularExpressions != NULL) {
		RegularExpression_free(regularExpressions->attribute.primitive);
		RegularExpression_free(regularExpressions->attribute.structure);
		RegularExpression_free(regularExpressions->attribute.primitive_array_0);
		RegularExpression_free(regularExpressions->attribute.primitive_array_1);
		RegularExpression_free(regularExpressions->attribute.primitive_array_2);
		RegularExpression_free(regularExpressions->attribute.structure_pointer_array_0);
		RegularExpression_free(regularExpressions->attribute.structure_array_1);
		RegularExpression_free(regularExpressions->attribute.structure_pointer_array_2);
		RegularExpression_free(regularExpressions->structure.start);
		RegularExpression_free(regularExpressions->structure.end);
		free(regularExpressions);
		regularExpressions = NULL;
	}
}

Structure * RegularExpressions_parse_structure(char *name, char *file_name) {
	RegularExpressions *regularExpressions = RegularExpressions_create(name);
	
	char *struct_body;
	{
		size_t struct_body_length;
		FILE *struct_body_stream = NULL;
		
		ssize_t read;
		FILE *f = NULL;
		if ((f = fopen(file_name, "r"))==NULL) {
			printf("No such file or can't open it!\n");
			RegularExpressions_free(regularExpressions);
			return NULL;
		}
		size_t line_length = 0;
		char *line = NULL;
		while ((read = getline(&line, &line_length, f)) != -1) {
			if (struct_body_stream==NULL && RegularExpression_match(regularExpressions->structure.start, line)) {
				struct_body_stream = open_memstream(&struct_body, &struct_body_length);
			} else if (struct_body_stream!=NULL) {
				if (!RegularExpression_match(regularExpressions->structure.end, line)) {
					fprintf(struct_body_stream, "%s", line);
				} else {
					fclose(struct_body_stream);
					break;
				} 
			}
		}
		fclose(f);
		free(line);
	}
	Structure *structure = Structure_create(name, file_name);
	{
		char *line;
		for (line=strtok(struct_body, "\n"); line!=NULL; line=strtok(NULL, "\n")) {
			RegularExpressions_parse_attribute_for_structure(regularExpressions, structure, line);
		}
		free(line);
	}
	{
		RegularExpressions_free(regularExpressions);
		free(struct_body);
	}
	return structure;
}

Boolean RegularExpressions_parse_attribute_for_structure(RegularExpressions *regularExpressions, Structure *structure, char *line) {
	RegularExpression *re = NULL;
	AttributeType type = NO_TYPE;
	Attribute *attribute = NULL;
	int flag_array = 0b00;
	size_t num_matches = 0;
	char **matches = NULL;
	if (
		(
			((re=regularExpressions->attribute.primitive) && (type=PRIMITIVE)) && 
			RegularExpression_match(re, line)
		) || (
			((re=regularExpressions->attribute.structure) && (type=STRUCTURE)) && 
			RegularExpression_match(re, line)
		)
	) {
		num_matches = re->num_matches;
		matches = RegularExpression_parse(re, line);
		char *data_type = matches[0];
		char *name = matches[1];
		Dimension *dimension = NULL;
		attribute = Attribute_create(type, data_type, name, dimension);
	} else if (
		(
			((re=regularExpressions->attribute.primitive_array_0) && (type=PRIMITIVE_ARRAY) && (flag_array=0b10)) &&
			RegularExpression_match(re, line)
		) || (
			((re=regularExpressions->attribute.primitive_array_1) && (type=PRIMITIVE_ARRAY) && (flag_array=0b01)) &&
			RegularExpression_match(re, line)
		) || (
			((re=regularExpressions->attribute.primitive_array_2) && (type=PRIMITIVE_ARRAY) && (flag_array=0b11)) &&
			RegularExpression_match(re, line)
		) || (
			((re=regularExpressions->attribute.structure_pointer_array_0) && (type=STRUCTURE_POINTER_ARRAY) && (flag_array=0b10)) &&
			RegularExpression_match(re, line)
		) || (
			((re=regularExpressions->attribute.structure_array_1) && (type=STRUCTURE_ARRAY) && (flag_array=0b01)) &&
			RegularExpression_match(re, line)
		) || (
			((re=regularExpressions->attribute.structure_pointer_array_2) && (type=STRUCTURE_POINTER_ARRAY) && (flag_array=0b11)) &&
			RegularExpression_match(re, line)
		)
	)	{
		num_matches = re->num_matches;
		matches = RegularExpression_parse(re, line);
		char *data_type = matches[0];
		char *name = (flag_array==0b01) ? matches[1] : matches[2];
		size_t static_size = (flag_array & 0b01) ? 
			({
				int size = 0;
				char *match = (flag_array & 0b10) ? matches[3] : matches[2];
				for (int i=0; i<strlen(match); i++) {
					if (match[i] == '[') {
						size = size + 1;
					}
				}
				size;
			}) : 0;
		size_t dynamic_size = (flag_array & 0b10) ? strlen(matches[1]) : 0;
		Dimension *dimension = Dimension_create(static_size, dynamic_size);
		if (flag_array & 0b01) {
			char *match = (flag_array & 0b10) ? matches[3] : matches[2];
			char *buff = (char *)calloc(16, sizeof(char));
			for (int i=0, str_start=0; i<static_size; i++) {
				sscanf(match+str_start, "[%[^]]s]", buff);
				str_start += 1 + strlen(buff) + 1;
				Dimension_set_dimension(dimension, i, buff);
			}
			free(buff);
		}
		size_t dimension_attributes = 0;
		{
			for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
				if (strlen(name)<strlen(curr->name) && strncmp(name, curr->name, strlen(name))==0) {
					dimension_attributes = dimension_attributes + 1;
				}
			}
		}
		{
			int index = -1;
			if (type==PRIMITIVE_ARRAY && string_equals(data_type, "char") && (dimension_attributes==0 && static_size+dynamic_size==1)) {
				type = STRING;
				data_type = "string";
				index = -1;
				dimension->size = dimension->size - 1;
			} else if (type==PRIMITIVE_ARRAY && string_equals(data_type, "char") && (dimension_attributes==0 && static_size>1 && dynamic_size==0)) {
				type = STRING_ARRAY;
				data_type = "string";
				index = -1;
				dimension->size = dimension->size - 1;
			} else if (type==PRIMITIVE_ARRAY && string_equals(data_type, "char") && dimension_attributes+1==dynamic_size) {
				type = STRING_ARRAY;
				data_type = "string";
				index = static_size;
				dimension->size = dimension->size - 1;
			} else if (type==PRIMITIVE_ARRAY && string_equals(data_type, "char") && dimension_attributes+1==static_size+dynamic_size) {
				type = STRING_ARRAY;
				data_type = "string";
				index = 0;
				dimension->size = dimension->size - 1;
				dimension->static_size = 0;
				dimension->dynamic_size = dimension->size;
			} else if (type==PRIMITIVE_ARRAY && dimension_attributes==dynamic_size) {
				index = static_size;
			} else if (type==PRIMITIVE_ARRAY && dimension_attributes==static_size+dynamic_size) {
				index = 0;
				dimension->static_size = 0;
				dimension->dynamic_size = dimension->size;
			} else if (type==STRUCTURE_POINTER_ARRAY && (dimension_attributes==0 && dynamic_size==1)) {
				type = STRUCTURE_POINTER;
				index = -1;
				dimension->size = dimension->size - 1;
			} else if (type==STRUCTURE_POINTER_ARRAY && dimension_attributes+1==dynamic_size) {
				index = static_size;
				dimension->size = dimension->size - 1;
			} else if (type==STRUCTURE_POINTER_ARRAY && dimension_attributes==dynamic_size) {
				type = STRUCTURE_ARRAY;
				index = static_size;
			} else if (type==STRUCTURE_ARRAY && dimension_attributes==static_size+dynamic_size) {
				index = 0;
			} else if (type==STRUCTURE_POINTER_ARRAY && dimension_attributes+1==static_size+dynamic_size) {
				index = 0;
				dimension->size = dimension->size - 1;
				dimension->static_size = 0;
				dimension->dynamic_size = dimension->size;
			} else if (type==STRUCTURE_POINTER_ARRAY && dimension_attributes==static_size+dynamic_size) {
				type = STRUCTURE_ARRAY;
				index = 0;
				dimension->static_size = 0;
				dimension->dynamic_size = dimension->size;
			}
			for (Attribute *curr=structure->head, *to_delete=NULL; curr!=NULL; curr=curr->next, Structure_delete(structure, to_delete), to_delete=NULL) {
				if (strlen(name)<strlen(curr->name) && strncmp(name, curr->name, strlen(name))==0) {
					to_delete = curr;
					Dimension_set_dimension(dimension, index, curr->name);
					index = index + 1;
				}
			}
		}
		attribute = Attribute_create(type, data_type, name, dimension);
	}
	{
		re = NULL;
		type = NO_TYPE;
		flag_array = 0;
		if (matches != NULL) {
			for (int i=0; i<num_matches; i++) {
				if (matches[i] != NULL) {
					free(matches[i]);
				}
			}
			num_matches = 0;
			free(matches);
			matches = NULL;
		}
	}
	if (attribute != NULL) {
		Structure_add(structure, attribute);
		attribute = NULL;
		return true;
	}
	return false;
}
