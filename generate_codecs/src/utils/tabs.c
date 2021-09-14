#include <stdio.h>
#include <stdlib.h>

#include "utils/tabs.h"


Tabs * Tabs_create() {
	Tabs *tabs = (Tabs *)malloc(sizeof(Tabs));
	tabs->string_length_max = 32;
	tabs->string_length = 0;
	tabs->string = (char *)calloc(tabs->string_length_max+1, sizeof(char));
	return tabs;
}

void Tabs_free(Tabs *tabs) {
	if (tabs != NULL) {
		tabs->string_length_max = 0;
		tabs->string_length = 0;
		if (tabs->string != NULL) {
			free(tabs->string);
			tabs->string = NULL;
		}
		free(tabs);
		tabs = NULL;
	}
}

char * Tabs_to_string(Tabs *tabs) {
	char *tabs_string;
	{
		size_t tabs_string_length;
		FILE *tabs_string_stream = open_memstream(&tabs_string, &tabs_string_length);
		fprintf(tabs_string_stream, "Tabs [%ld/%ld]: \'%s\'", tabs->string_length, tabs->string_length_max, tabs->string);
		fclose(tabs_string_stream);
	}
	return tabs_string;
}

char * Tabs_get(Tabs *tabs) {
	return tabs->string;
}

void Tabs_increment(Tabs *tabs) {
	if (tabs->string_length < tabs->string_length_max) {
		tabs->string[tabs->string_length] = '\t';
		tabs->string_length = tabs->string_length + 1;
	}
}

void Tabs_decrement(Tabs *tabs) {
	if (tabs->string_length > 0) {
		tabs->string_length = tabs->string_length - 1;
		tabs->string[tabs->string_length] = 0;
	}
}
