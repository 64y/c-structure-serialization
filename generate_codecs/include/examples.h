#ifndef EXAMPLES_H
#define EXAMPLES_H


void example_utils_basic_defines();
void example_utils_tabs();
void example_data_types_data_type();
void example_data_types_dimension();
void example_data_types_attribute();
void example_data_types_structure();


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
	puts("utils/tabs\n");
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


#include "data_types/data_type.h"

void example_data_types_data_type() {
	puts("data_types/data_type\n");
	BasicType *basicType = get_basic_type_by_name("string");
	char *basicType_string = BasicType_to_string(basicType);
	puts(basicType_string);
	{
		free(basicType_string);
	}
	puts("\n");
}


#include "data_types/dimension.h"

void example_data_types_dimension() {
	puts("data_types/dimension\n");
	Dimension *dimension = Dimension_create(2, 2);
	Dimension_set_dimension(dimension, 0, "40");
	Dimension_set_dimension(dimension, 1, "50");
	Dimension_set_dimension(dimension, 2, "n");
	Dimension_set_dimension(dimension, 2, "m");
	char *dimension_string = Dimension_to_string(dimension);
	puts(dimension_string);
	{
		Dimension_free(dimension);
		free(dimension_string);
	}
	puts("\n");
}


#include "data_types/attribute.h"

void example_data_types_attribute() {
	puts("data_types/attribute\n");
	Attribute *attribute = Attribute_create(STRUCTURE_POINTER, "Cat", "cat", NULL); // Cat *cat;
	char *attribute_string = Attribute_to_string(attribute);
	puts(attribute_string);
	{
		Attribute_free(attribute);
		free(attribute_string);
	}
	puts("\n");
}


#include "data_types/structure.h"

void example_data_types_structure() {
	puts("data_types/structure\n");
	Attribute *color;
	Structure *structure;
	{
		color = Attribute_create(STRING, "char", "color", NULL);
		
		structure = Structure_create("Cat", "structures/cat.h");
		Structure_add(structure, Attribute_create(STRING, "char", "name", NULL));
		Structure_add(structure, Attribute_create(PRIMITIVE, "int", "age", NULL));
		Structure_add(structure, color);
		Structure_add(structure, Attribute_create(STRUCTURE_POINTER, "Cat", "next", NULL));
	}
	printf("Structure has structure\'s attributes: %s!\n", Boolean_to_string(Structure_has_structure_attributes(structure)));
	
	char *structure_string_before_delete = Structure_to_string(structure);
	puts("Structure before delete:");
	puts(structure_string_before_delete);
	
	Structure_delete(structure, color);
	char *structure_string_after_delete = Structure_to_string(structure);
	puts("Structure after delete:");
	puts(structure_string_after_delete);
	
	{
		color = NULL;
		Structure_free(structure);
		free(structure_string_before_delete);
		free(structure_string_after_delete);
	}
	puts("\n");
}

#endif
