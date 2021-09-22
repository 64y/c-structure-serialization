#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "c_structure_serialization/utils/array.h"
#include "c_structure_serialization/utils/boolean.h"
#include "c_structure_serialization/utils/strings.h"


char * string_copy(char *string) {
	char *string_copy = (char *)calloc(strlen(string)+1, sizeof(char));
	strcpy(string_copy, string);
	return string_copy;
}

Boolean string_equals(char *string0, char *string1) {
	return (strcmp(string0, string1)==0)? true : false;
}

Boolean string_equals_r(char *string0, char *string1) {
	size_t string0_length = strlen(string0);
	size_t string1_length = strlen(string1);
	for (int string0_i=string0_length-1, string1_i=string1_length-1; string0_i>=0 && string1_i>=0; string0_i--, string1_i--) {
		if (string0[string0_i] != string1[string1_i]) {
			return false;
		}
	}
	return true;
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

char * string_to_upper_safe(char *string) {
	size_t string_upper_length = strlen(string);
	char *string_upper = string_to_upper(string);
	for (int i=0; i<string_upper_length; i++) {
		if (string[i] == ' ') {
			string_upper[i] = '_';
		}
	}
	return string_upper;
}

char * string_make_shortcut(char *string) {
	char *shortcut = (char *)calloc(strlen(string)+1, sizeof(char));
	strcpy(shortcut, string);
	shortcut[0] = tolower(shortcut[0]);
	return shortcut;
}

char * string_appends(char *strings[]) {
	size_t string_length = 0;
	for (int i=0; strings[i]!=NULL; i++) {
		string_length += strlen(strings[i]);
	}
	char *string = (char *)calloc(string_length+1, sizeof(char));
	for (int i=0, string_index=0; strings[i]!=NULL; i++) {
		for (int index=0; index<strlen(strings[i]); string_index++, index++) {
			string[string_index] = strings[i][index];
		}
	}
	return string;
}

char * string_random(size_t string_length_min, size_t string_length_max) {
	size_t string_printable_length = 96;
	char *string_printable = "0123456789qwertyuiopasdfgghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM`~!@#$%%^&*()-_=+[{]}\\|;:\'\",<.>/?";
	size_t string_length = string_length_min + random()%(string_length_max+1-string_length_min);
	char *string = (char *)calloc(string_length+1, sizeof(char));
	for (int i=0; i<string_length; i++) {
		string[i] = string_printable[random() % string_printable_length];
	}
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
