#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils/basic_defines.h"
#include "utils/tabs.h"
#include "data_types/data_type.h"
#include "data_types/dimension.h"
#include "data_types/attribute.h"
#include "data_types/structure.h"
#include "data_types/structures_regular_expressions.h"
#include "serialization/registrate.h"
#include "serialization/serialize.h"


#include "examples/0_primitives.h"
#include "examples/1_string.h"
#include "examples/2_array.h"
#include "examples/3_matrices.h"
#include "examples/4_structures.h"
#include "examples/5_matrices_of_structures.h"

void examples_run_all() {
	example_of_structure_with_primitives_members();
	example_of_structure_with_string_member();
	example_of_structure_with_array();
	example_of_structure_with_matrix();
	example_of_structure_with_matrices();
	example_of_structure_with_matrices_of_strings();
	example_of_structure_with_structures_and_structures_pointers();
	example_of_structure_with_matrices_of_structures();
}


void test_utils_basic_defines();
void test_utils_tabs();
void test_data_types_data_type();
void test_data_types_attribute();
void test_data_types_structure();
void test_data_types_structures_regular_expressions();
void tests_all();


void test_utils_basic_defines() {
	puts("utils/basic_defines");
	{ // test Boolean_to_string
		puts("basic_defines: Boolean_to_string");
		Boolean b = false;
		char *b_string = Boolean_to_string(b);
		printf("b = \"%s\"\n", b_string);
		puts("\n");
	}
	{ // test string_copy
		puts("basic_defines: string_copy");
		char *string = string_copy("the very first string");
		printf("string = \"%s\"\n", string);
		{
			free(string);
		}
		puts("\n");
	}
	{ // test string_equals
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
	{ //test string_to_lower
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
	{ //test string_to_upper
		puts("basic_defines: string_to_upper");
		char *string = string_copy("Hello World!");
		char *string_upper = string_to_upper(string);
		printf("upper(\"%s\") = \"%s\"\n", string, string_upper);
		{
			free(string);
			free(string_upper);
		}
	}
	{ //test string_make_shortcut
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
	{ //test string_appends
		puts("basic_defines: string_appends");
		char *string = string_appends((char *[]) {"Hello", " ", "World", "!", NULL});
		puts(string);
		{
			free(string);
		}
		puts("\n");
	}
	{ //test string_random
		puts("basic_defines: string_random");
		char *string = string_random(10, 20);
		puts(string);
		{
			free(string);
		}
		puts("\n");
	}
	{ //test file_write & file_read
		puts("basic_defines: file_write & file_read");
		file_write("a.txt", "Sorry, it is empty!");
		char *text = file_read("a.txt");
		{
			free(text);
		}
		puts("\n");
	}
	{ //test path_get_dir
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

void test_utils_tabs() {
	puts("utils/Tabs");
	Tabs *tabs = Tabs_create();
	Tabs_increment(tabs); Tabs_increment(tabs); Tabs_increment(tabs);
	char *tabs_string = Tabs_to_string(tabs);
	char *tabs_get = Tabs_get(tabs);
	puts(tabs_string);
	printf("\"%s\"\n", tabs_get);
	Tabs_decrement(tabs); Tabs_decrement(tabs); Tabs_decrement(tabs); Tabs_decrement(tabs);
	{
		free(tabs_string);
		Tabs_free(tabs);
	}
	puts("\n");
}

void test_data_types_data_type() {
	puts("data_types/data_type");
	BasicType *basicType = get_basic_type_by_name("string");
	char *basicType_string = BasicType_to_string(basicType);
	puts(basicType_string);
	{
		free(basicType_string);
	}
	puts("\n");
}

void test_data_types_dimension() {
	puts("data_types/Dimension");
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

void test_data_types_attribute() {
	// Cat cat = NULL;
	puts("data_types/Attribute");
	Attribute *attribute = Attribute_create(STRUCTURE, "Cat", "cat", NULL);
	char *attribute_string = Attribute_to_string(attribute);
	puts(attribute_string);
	{
		Attribute_free(attribute);
		free(attribute_string);
	}
	puts("\n");
}

void test_data_types_structure() {
	puts("data_types/Structure");
	Structure *structure = Structure_create("Cat", "structures/test_2.h");
	{
		Structure_add(structure, Attribute_create(STRING, "char", "name", NULL));
		Structure_add(structure, Attribute_create(PRIMITIVE, "int", "age", NULL));
		Structure_add(structure, Attribute_create(STRING, "char", "color", NULL));
		Structure_add(structure, Attribute_create(STRUCTURE_POINTER, "Cat", "next", NULL));
		Structure_has_structure_attributes(structure);
	}
	char *structure_string = Structure_to_string(structure);
	puts(structure_string);
	{
		Structure_free(structure);
		free(structure_string);
	}
	puts("\n");
}

void test_data_types_structures_regular_expressions() {
	puts("data_types/RegularExpression");
	{
		size_t lines_size = 3;
		char *lines[] = {
			"\tint a;",
			"\tchar *b;",
			"\tCat *c;"
		};
		for (int i=0; i<lines_size; i++) {
			puts("          /RegularExpression");
			puts(lines[i]);
			char *line = string_copy(lines[i]);
			RegularExpression *primitive = RegularExpression_create("(char|unsighed\\schar|byte|short|int|long|float|double)\\s([0-9a-zA-Z_]+);", 2);
			if (true) {
				puts("data_types/RegularExpression: to_string");
				char *primitive_string = RegularExpression_to_string(primitive);
				puts(primitive_string);
				free(primitive_string);
			}
			if (true) {
				puts("data_types/RegularExpression: RegularExpression_match");
				printf("- Does \"%s\" primitive?\n%s\n", line, (RegularExpression_match(primitive, line)) ? "YES" : "NO");
			}
			if (true) {
				puts("data_types/RegularExpression: RegularExpression_parse");
				char **matches = RegularExpression_parse(primitive, line);
				if (matches != NULL) {
					printf("Match #1: \'%s\', match #2: \'%s\'.\n", matches[0], matches[1]);
					free(matches[0]);
					free(matches[1]);
					free(matches);
				} else {
					puts("No Matches!");
				}
			}
			{
				free(line);
				RegularExpression_free(primitive);
			}
			puts("\n");
		}
	}
	{
		puts("data_types/RegularExpression: RegularExpressions_parse_structure");
		Structure *structure = RegularExpressions_parse_structure("Cat", "src/structures/test_2.h");
		char *structure_string = Structure_to_string(structure);
		puts(structure_string);
		{
			Structure_free(structure);
			free(structure_string);
		}
	}
}

void tests_all() {
	test_utils_basic_defines();
	test_utils_tabs();
	test_data_types_data_type();
	test_data_types_attribute();
	test_data_types_structure();
	test_data_types_structures_regular_expressions();
}

#endif
