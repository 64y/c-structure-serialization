#ifndef TABS_H
#define TABS_H


#include <stddef.h>


typedef struct Tabs {
	size_t tab_length;
	char *tab;
	size_t string_length;
	size_t string_length_max;
	char *string;
} Tabs;

Tabs * Tabs_create();
Tabs * Tabs_create_by_tab(char *tab);
void Tabs_free(Tabs *tabs);
char * Tabs_to_string(Tabs *tabs);

char * Tabs_get_tab(Tabs *tabs);
char * Tabs_get(Tabs *tabs);
void Tabs_increment(Tabs *tabs);
void Tabs_decrement(Tabs *tabs);

#endif
