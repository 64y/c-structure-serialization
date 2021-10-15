#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_structure_serialization/utils/array.h"
#include "c_structure_serialization/utils/strings.h"


char * string_create(char *string) {
	char *string_copy = (char *)calloc(strlen(string)+1, sizeof(char));
	strcpy(string_copy, string);
	return string_copy;
}

char * string_create_by_format(char *string_format, ...) {
	va_list string_arguments;
	va_start(string_arguments, string_format);
	char *string;
	{
		size_t string_length;
		FILE *string_stream = open_memstream(&string, &string_length);
		vfprintf(string_stream, string_format, string_arguments);
		{
			fclose(string_stream);
		}
	}
	va_end(string_arguments);
	return string;
}

void string_free(char *string) {
	if (string!=NULL) {
		free(string);
		string = NULL;
	}
}

bool string_equals(char *stringA, char *stringB) {
	return (strcmp(stringA, stringB)==0)?true:false;
}

bool string_ends_with(char *string, char *end) {
	size_t string_length = strlen(string);
	size_t end_length = strlen(end);
	for (int string_i=string_length-1, end_i=end_length-1; string_i>=0 && end_i>=0; string_i--, end_i--) {
		if (string[string_i]!=end[end_i]) {
			return false;
		}
	}
	return true;
}

char * string_copy(char *string) {
	return string_create(string);
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

char * string_replace_char(char *string, char find, char replace) {
	size_t string_length = strlen(string);
	char *string_replaced = (char *)calloc(string_length+1, sizeof(char));
	for (int i=0; i<string_length; i++) {
		string_replaced[i] = (string[i]==find)?replace:string[i];
	}
	return string_replaced;
}

char * string_appends(char *string_first, ...) {
	va_list ap;
	va_start(ap, string_first);
	char *string;
	{
		size_t string_length;
		FILE *string_stream = open_memstream(&string, &string_length);
		if (string_first!=NO_MORE_STRINGS) {
			fprintf(string_stream, "%s", string_first);
			while (1) {
				char *str = va_arg(ap, char *);
				if (str==NO_MORE_STRINGS) {
					break;
				}
				fprintf(string_stream, "%s", str);
			}
		} else {
			fprintf(string_stream, "%s", "");
		}
		{
			fclose(string_stream);
		}
	}
	va_end(ap);
	return string;
}

char * string_make_shortcut(char *string) {
	size_t string_length = strlen(string);
	char *string_shortcut = (char *)calloc(1+string_length+1, sizeof(char));
	strcpy(string_shortcut, string);
	string_shortcut[0] = '_';
	string_shortcut[1] = tolower(string_shortcut[1]);
	return string_shortcut;
}

char * string_repeat_star(size_t times) {
	if (times==0) {
		return string_create("");
	}
	char *string = (char *)calloc(1+times+1, sizeof(char));
	string[0] = ' '; 
	memset(string+1, '*', times);
	return string;
}


void * array_string_create(void *element_create_arguments) {
	return string_copy((char *) element_create_arguments);
}

void array_string_free(void *element) {
	free((char *)element);
}

char * array_string_to_string(void *element) {
	return string_copy((char *) element);
}

int array_string_cmp(const void *a, const void *b) {
	return strcmp(*(char **) a, *(char **) b);
}

Array * Array_create_for_string() {
	return Array_create(array_string_create, array_string_free, array_string_to_string);
}
