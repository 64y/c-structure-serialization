#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/utils/tabs.h"


Tabs * Tabs_create() {
	return Tabs_create_by_tab("\t");
}

Tabs * Tabs_create_by_tab(char *tab) {
	Tabs *tabs = (Tabs *)malloc(sizeof(Tabs));
	tabs->tab_length = strlen(tab);
	tabs->tab = string_copy(tab);
	tabs->string_length = 0;
	tabs->string_length_max = 32;
	tabs->string = (char *)calloc(tabs->tab_length*tabs->string_length_max+1, sizeof(char));
	return tabs;
}

void Tabs_free(Tabs *tabs) {
	if (tabs!=NULL) {
		tabs->tab_length = 0;
		if (tabs->tab!=NULL) {
			string_free(tabs->tab);
		}
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
		"tab_length: \'%ld\';\n"
		"tab: \'%s\';"
		"string length: \'%ld\';\n"
		"string length max: \'%ld\';\n"
		"string: \'%s\'.",
		(long)(void *)tabs, tabs->tab_length, tabs->tab, tabs->string_length, tabs->string_length_max, tabs->string
	);
	return tabs_string;
}

char * Tabs_get_tab(Tabs *tabs) {
	return tabs->tab;
}

char * Tabs_get(Tabs *tabs) {
	return tabs->string;
}

void Tabs_increment(Tabs *tabs) {
	if (tabs->string_length<tabs->string_length_max) {
		memcpy(tabs->string+(tabs->tab_length*tabs->string_length), tabs->tab, tabs->tab_length);
		tabs->string_length = tabs->string_length+1;
	}
}

void Tabs_decrement(Tabs *tabs) {
	if (tabs->string_length>0) {
		tabs->string_length = tabs->string_length-1;
		memset(tabs->string+(tabs->tab_length*tabs->string_length), 0x00, tabs->tab_length);
	}
}
