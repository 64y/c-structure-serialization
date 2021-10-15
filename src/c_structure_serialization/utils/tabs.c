#include <stdio.h>
#include <stdlib.h>

#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/utils/tabs.h"


Tabs * Tabs_create() {
	Tabs *tabs = (Tabs *)malloc(sizeof(Tabs));
	tabs->string_length = 0;
	tabs->string_length_max = 32;
	tabs->string = (char *)calloc(tabs->string_length_max+1, sizeof(char));
	return tabs;
}

void Tabs_free(Tabs *tabs) {
	if (tabs!=NULL) {
		tabs->string_length = 0;
		tabs->string_length_max = 0;
		if (tabs->string!=NULL) {
			string_free(tabs->string);
		}
		free(tabs);
		tabs = NULL;
	}
}

char * Tabs_to_string(Tabs *tabs) {
	char *tabs_string = string_create_by_format(
		"Tabs@%lX\n"
		"string length: \'%ld\';\n"
		"string length max: \'%ld\';\n"
		"string: \'%s\'.",
		(long)(void *)tabs, tabs->string_length, tabs->string_length_max, tabs->string
	);
	return tabs_string;
}


char * Tabs_get(Tabs *tabs) {
	return tabs->string;
}

void Tabs_increment(Tabs *tabs) {
	if (tabs->string_length<tabs->string_length_max) {
		tabs->string[tabs->string_length] = '\t';
		tabs->string_length = tabs->string_length+1;
	}
}

void Tabs_decrement(Tabs *tabs) {
	if (tabs->string_length>0) {
		tabs->string_length = tabs->string_length-1;
		tabs->string[tabs->string_length] = 0;
	}
}
