#ifndef TABS_H
#define TABS_H


typedef struct Tabs {
	size_t string_length_max;
	size_t string_length;
	char *string;
} Tabs;

Tabs * Tabs_create();
void Tabs_free(Tabs *tabs);
char * Tabs_to_string(Tabs *tabs);
char * Tabs_get(Tabs *tabs);
void Tabs_increment(Tabs *tabs);
void Tabs_decrement(Tabs *tabs);

#endif
