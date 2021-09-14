#ifndef EXAMPLES_H
#define EXAMPLES_H

void example_utils_basic_defines();
void test_utils_tabs();


#include "utils/basic_defines.h"

void example_utils_basic_defines() {
	puts("utils/basic_defines\n");
	{ // example Boolean_to_string
		puts("basic_defines: Boolean_to_string");
		Boolean b = true;
		char *b_string = Boolean_to_string(b);
		printf("b (%d) = \"%s\"\n", b, b_string);
		puts("\n");
	}
	{ // example string_copy
		puts("basic_defines: string_copy");
		char *string = string_copy("the very first string");
		printf("string = \"%s\"\n", string);
		{
			free(string);
		}
		puts("\n");
	}
	{ // example string_equals
		puts("basic_defines: string_equals");
		char *string0=string_copy("qwer"), *string1=string_copy("asdf"), *string2=string_copy("asdf");
		char *string_equals01 = Boolean_to_string(string_equals(string0, string1));
		char *string_equals12 = Boolean_to_string(string_equals(string1, string2));
		printf("\"%s\"=\"%s\" - %s\n", string0, string1, string_equals01);
		printf("\"%s\"=\"%s\" - %s\n", string1, string2, string_equals12);
		{
			free(string0);
			free(string1);
			free(string2);
		}
		puts("\n");
	}
	{ // example string_to_lower
		puts("basic_defines: string_to_lower");
		char *string = string_copy("Hello World!");
		char *string_lower = string_to_lower(string);
		printf("lower(\"%s\") = \"%s\"\n", string, string_lower);
		{
			free(string);
			free(string_lower);
		}
		puts("\n");
	}
	{ // example string_to_upper
		puts("basic_defines: string_to_upper");
		char *string = string_copy("Hello World!");
		char *string_upper = string_to_upper(string);
		printf("upper(\"%s\") = \"%s\"\n", string, string_upper);
		{
			free(string);
			free(string_upper);
		}
		puts("\n");
	}
	{ //example string_make_shortcut
		puts("basic_defines: string_make_shortcut");
		char *string = string_copy("LongValue");
		char *string_shortcut = string_make_shortcut(string);
		printf("shortcut(\"%s\") = \"%s\"\n", string, string_shortcut);
		{
			free(string);
			free(string_shortcut);
		}
		puts("\n");
	}
	{ // example string_appends
		puts("basic_defines: string_appends");
		char *string = string_appends((char *[]) {"Hello", " ", "World", "!", NULL});
		puts(string);
		{
			free(string);
		}
		puts("\n");
	}
	{ //example string_random
		puts("basic_defines: string_random");
		char *string = string_random(10, 20);
		puts(string);
		{
			free(string);
		}
		puts("\n");
	}
	{ // example file_write & file_read
		puts("basic_defines: file_write & file_read");
		file_write("a.txt", "Sorry, it is empty!");
		char *text = file_read("a.txt");
		puts(text);
		{
			free(text);
		}
		puts("\n");
	}
	{ // example path_get_dir
		puts("basic_defines: path_get_dir");
		char *file_name = string_copy("src/main.c");
		char *dir = path_get_dir(file_name);
		printf("\"%s\" in \"%s\"\n", file_name, dir);
		{
			free(file_name);
			free(dir);
		}
		puts("\n");
	}
}


#include "utils/tabs.h"

void example_utils_tabs() {
	puts("utils/Tabs\n");
	Tabs *tabs = Tabs_create();
	Tabs_increment(tabs); Tabs_increment(tabs); Tabs_increment(tabs);
	char *tabs_string = Tabs_to_string(tabs);
	char *tabs_get = Tabs_get(tabs);
	puts(tabs_string);
	printf("\"%s\"\n", tabs_get);
	Tabs_decrement(tabs); Tabs_decrement(tabs); Tabs_decrement(tabs); Tabs_decrement(tabs);
	{
		Tabs_free(tabs);
		free(tabs_string);
	}
	puts("\n");
}



#endif
