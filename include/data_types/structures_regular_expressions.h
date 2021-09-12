#ifndef STRUCTURES_REGULAR_EXPRESSIONS_H
#define STRUCTURES_REGULAR_EXPRESSIONS_H

#include <regex.h>

#include "utils/basic_defines.h"
#include "data_types/attribute.h"
#include "data_types/structure.h"


typedef struct RegularExpression {
	char *pattern;
	size_t num_matches;
	regex_t *re;
} RegularExpression;

RegularExpression * RegularExpression_create(char *pattern, size_t num_matches);
void RegularExpression_free(RegularExpression *regularExpression);
char * RegularExpression_to_string(RegularExpression *regularExpression);
Boolean RegularExpression_match(RegularExpression *regularExpression, char *string);
char ** RegularExpression_parse(RegularExpression *regularExpression, char *string);


typedef struct RegularExpressions {
	struct {
		RegularExpression *primitive;
		RegularExpression *structure;
		RegularExpression *primitive_array_0;
		RegularExpression *primitive_array_1;
		RegularExpression *primitive_array_2;
		RegularExpression *structure_pointer_array_0;
		RegularExpression *structure_array_1;
		RegularExpression *structure_pointer_array_2;
	} attribute;
	struct {
		RegularExpression *start;
		RegularExpression *end;
	} structure;
} RegularExpressions;


RegularExpressions * RegularExpressions_create(char *struct_name);
void RegularExpressions_free(RegularExpressions *regularExpressions);

Structure * RegularExpressions_parse_structure(char *name, char *file_name);
Boolean RegularExpressions_parse_attribute_for_structure(RegularExpressions *regularExpressions, Structure *structure, char *line);

#endif
