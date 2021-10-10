#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "c_structure_serialization/utils/boolean.h"
#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/data_types/basic_type.h"
#include "c_structure_serialization/data_types/structure_regular_expressions.h"


RegularExpression * RegularExpression_create(char *pattern, size_t num_matches) {
	RegularExpression *regularExpression = (RegularExpression *)malloc(sizeof(RegularExpression));
	regularExpression->pattern = string_copy(pattern);
	regularExpression->num_matches = num_matches;
	regularExpression->re = (regex_t *)malloc(sizeof(regex_t));
	int error_code;
	if ((error_code=regcomp(regularExpression->re, regularExpression->pattern, REG_EXTENDED))!=0) {
		char *error_message = (char *)calloc(100+1, sizeof(char));
		regerror(error_code, regularExpression->re, error_message, 100);
		fprintf(stderr, "\'RegularExpression_create\' method can\'t create regular expression pattern from \"%s\" because of \"%s\"!\n", pattern, error_message);
		exit(1);
	}
	return regularExpression;
}

void RegularExpression_free(RegularExpression *regularExpression) {
	if (regularExpression!=NULL) {
		if (regularExpression->pattern!=NULL) {
			free(regularExpression->pattern);
			regularExpression->pattern = NULL;
		}
		regularExpression->num_matches = 0;
		if (regularExpression->re!=NULL) {
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
		FILE *regularExpression_string_stream = open_memstream(&regularExpression_string, &regularExpression_string_length);
		fprintf(
			regularExpression_string_stream,
			"RegularExpression@%lx\n"
			"pattern: \'%s\';\n"
			"num match: \'%ld\';\n"
			"re: @%lX.",
			(long)(void *) regularExpression, regularExpression->pattern, regularExpression->num_matches, (long)(void *) regularExpression->re
		);
		{
			fclose(regularExpression_string_stream);
		}
	}
	return regularExpression_string;
}

Boolean RegularExpression_match(RegularExpression *regularExpression, char *string) {
	return (regexec(regularExpression->re, string, 0, NULL, 0) == 0)?true:false;
}

char ** RegularExpression_parse(RegularExpression *regularExpression, char *string) {
	char **matches;
	int result;
	size_t nmatch = regularExpression->num_matches+1;
	regmatch_t *pmatch = (regmatch_t *)calloc(nmatch, sizeof(regmatch_t));
	if ((result=regexec(regularExpression->re, string, nmatch, pmatch, 0))==0) {
		matches = (char **)calloc(regularExpression->num_matches, sizeof(char *));
		for (int i=0; i<regularExpression->num_matches; i++) {
			size_t match_length;
			FILE *match_stream = open_memstream(&matches[i], &match_length);
			fprintf(match_stream, "%.*s", pmatch[1+i].rm_eo-pmatch[1+i].rm_so, &string[pmatch[1+i].rm_so]);
			{
				fclose(match_stream);
			}
		}
	} else {
		matches = NULL;
	}
	{
		free(pmatch);
	}
	return matches;
}

StructureRegularExpressions *structureRegularExpressions;

void StructureRegularExpressions_init() {
	structureRegularExpressions = (StructureRegularExpressions *)malloc(sizeof(StructureRegularExpressions));
	structureRegularExpressions->structureStart = RegularExpression_create("^(typedef\\s)?(struct\\s[a-zA-Z_$]{1}[a-zA-Z_$0-9]*)\\s?\\{", 2);
	structureRegularExpressions->attribute = NULL;
	{
		char *pattern;
		{
			size_t pattern_length;
			FILE *pattern_stream = open_memstream(&pattern, &pattern_length);
			fprintf(pattern_stream, "^\t");
			fprintf(pattern_stream, "(");
			for (int i=0; i<BASIC_TYPE_SIZE-1; i++) {
				for (int name_i=0; name_i<strlen(BASIC_TYPE[i].name); name_i++) {
					if (BASIC_TYPE[i].name[name_i]!=' ') {
						fprintf(pattern_stream, "%c", BASIC_TYPE[i].name[name_i]);
					} else {
						fprintf(pattern_stream, "\\s");
					}
				}
				fprintf(pattern_stream, "|");
			}
			fprintf(
				pattern_stream,
				"[a-zA-Z_$]{1}[a-zA-Z_$0-9]*"
				"|"
				"struct\\s[a-zA-Z_$]{1}[a-zA-Z_$0-9]*"
				")"
				"(\\s|\\s?[*]+\\s?)"
				"([a-zA-Z_$]{1}[a-zA-Z_$0-9]*)"
				"(|(\\[[0-9]+\\])+)"
				";"
			);
			{
				fclose(pattern_stream);
			}
		}
		structureRegularExpressions->attribute = RegularExpression_create(pattern, 4);
		{
			free(pattern);
		}
	}
	structureRegularExpressions->structureEnd = RegularExpression_create("^\\}\\s?([a-zA-Z_$]{1}[a-zA-Z_$0-9]*)?\\s?;", 1);
}

void StructureRegularExpressions_fini(){
	if (structureRegularExpressions!=NULL) {
		RegularExpression_free(structureRegularExpressions->structureStart);
		RegularExpression_free(structureRegularExpressions->attribute);
		RegularExpression_free(structureRegularExpressions->structureEnd);
		free(structureRegularExpressions);
		structureRegularExpressions = NULL;
	}
}

__attribute__((section(".init_array"), used)) static typeof(StructureRegularExpressions_init) *StructureRegularExpressions_init_p = StructureRegularExpressions_init;
__attribute__((section(".fini_array"), used)) static typeof(StructureRegularExpressions_fini) *StructureRegularExpressions_fini_p = StructureRegularExpressions_fini;
