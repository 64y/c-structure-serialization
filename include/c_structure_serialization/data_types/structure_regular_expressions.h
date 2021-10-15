#ifndef STRUCTURES_REGULAR_EXPRESSIONS_H
#define STRUCTURES_REGULAR_EXPRESSIONS_H


#include <stdbool.h>
#include <stddef.h>
#include <regex.h>


typedef struct RegularExpression {
	char *pattern;
	size_t num_matches;
	regex_t *re;
} RegularExpression;

RegularExpression * RegularExpression_create(char *pattern, size_t num_matches);
void RegularExpression_free(RegularExpression *regularExpression);
char * RegularExpression_to_string(RegularExpression *regularExpression);

bool RegularExpression_match(RegularExpression *regularExpression, char *string);
char ** RegularExpression_parse(RegularExpression *regularExpression, char *string);


typedef struct StructureRegularExpressions {
	RegularExpression *structureStart;
	RegularExpression *attribute;
	RegularExpression *structureEnd;
} StructureRegularExpressions;

extern StructureRegularExpressions *structureRegularExpressions;

void StructureRegularExpressions_init();
void StructureRegularExpressions_fini();

#endif
