#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void test_utils_array();
void test_utils_boolean();
void test_utils_files();
void test_utils_strings();
void test_utils_tabs();
void test_data_types_basic_type();
void test_data_types_dimension();
void test_data_types_attribute();
void test_data_types_structure();
void test_data_types_structures_regular_expression();
void test_data_types_structures_regular_expressions();
void test_all();


int main(int argc, char *argv[]) {
	test_all();
	return 0;
}


#include "c_structure_serialization/utils/boolean.h"

void test_utils_boolean() {
	puts("utils/boolean\n");
	{ // example Boolean_to_string
		puts("basic_defines: Boolean_to_string");
		Boolean b = true;
		char *b_string = Boolean_to_string(b);
		printf("b (%d) = \"%s\"\n", b, b_string);
		puts("\n");
	}
}


#include "c_structure_serialization/utils/strings.h"

void test_utils_strings() {
	puts("utils/strings\n");
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
}


#include "c_structure_serialization/utils/files.h"

void test_utils_files() {
	puts("utils/files\n");
	{ // example file_write & file_read
		puts("basic_defines: file_write & file_read");
		file_write("a.txt", "Sorry, it is empty!\nReally it is empty and test for memmory leaks!\nKAPPAD\n...");
		char *text = file_read("a.txt");
		puts(text);
		{
			free(text);
		}
		puts("\n");
	}
	{ // example file_get_directory_path
		puts("basic_defines: file_get_directory_path");
		char *file_path = string_copy("main.c");
		char *directory_path = file_get_directory_path(file_path);
		printf("\"%s\" in \"%s\"\n", file_path, directory_path);
		{
			free(file_path);
			free(directory_path);
		}
		puts("\n");
	}
}


#include "c_structure_serialization/utils/tabs.h"

void test_utils_tabs() {
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


#include "c_structure_serialization/utils/array.h"

void test_utils_array() {
	void * array_string_create(void *element) {
		return string_copy((char *) element);
	}
	void array_string_free(void *element) {
		free((char *)element);
	}
	char * array_string_to_string(void *element) {
		return string_copy((char *) element);
	}

	Array * Array_of_string_create() {
		return Array_create(array_string_create, array_string_free, array_string_to_string);
	}
	puts("utils/array\n");
	/*{
		Array *a = Array_of_Structure_create();
		Array_add(a, array_Structure_arguments("structure/cat.h", "Cat"));
		Array_add(a, array_Structure_arguments("structure/dog.h", "Dog"));
		Array_add(a, array_Structure_arguments("structure/Pets.h", "Pets"));
		char *a_string = Array_to_string(a);
		puts(a_string);
		{
			Array_free(a);
			free(a_string);
		}
	}*/
	{
		Array *s = Array_of_string_create();
		Array_add(s, "qwer");
		Array_add(s, "asdf");
		Array_add(s, "zxcv");
		Array_add(s, "tyui");
		Array_add(s, "ghjk");
		Array_add(s, "bnml");
		Array_add(s, "op");
		char *s_string = Array_to_string(s);
		puts(s_string);
		{
			Array_free(s);
			free(s_string);
		}
	}
}


#include "c_structure_serialization/data_types/basic_type.h"

void test_data_types_basic_type() {
	puts("data_types/data_type\n");
	BasicType *basicType = get_basic_type_by_name("char *");
	char *basicType_string = BasicType_to_string(basicType);
	puts(basicType_string);
	{
		free(basicType_string);
	}
	puts("\n");
}


#include "c_structure_serialization/data_types/dimension.h"

void test_data_types_dimension() {
	puts("data_types/dimension\n");
	Dimension *dimension = Dimension_create(2, 2);
	Dimension_set_dimension(dimension, 0, "40");
	Dimension_set_dimension(dimension, 1, "50");
	Dimension_set_dimension(dimension, 2, "n");
	Dimension_set_dimension(dimension, 3, "m");
	char *dimension_string = Dimension_to_string(dimension);
	puts(dimension_string);
	{
		Dimension_free(dimension);
		free(dimension_string);
	}
	puts("\n");
}


#include "c_structure_serialization/data_types/attribute.h"

void test_data_types_attribute() {
	puts("data_types/attribute\n");
	Attribute *attribute;
	{
		// int cat_n;
		// int cat_m;
		// Cat ***cat[10][20][30];
		Dimension *dimension = Dimension_create(3, 2);
		Dimension_set_dimension(dimension, 0, "10");
		Dimension_set_dimension(dimension, 1, "15");
		Dimension_set_dimension(dimension, 2, "20");
		Dimension_set_dimension(dimension, 3, "n");
		Dimension_set_dimension(dimension, 4, "m");
		attribute = Attribute_create(STRUCTURE_POINTER, "Cat", "cat", dimension);
	}
	char *attribute_string = Attribute_to_string(attribute);
	puts(attribute_string);
	{
		Attribute_free(attribute);
		free(attribute_string);
	}
	puts("\n");
}


#include "c_structure_serialization/data_types/structure.h"

void test_data_types_structure() {
	puts("data_types/structure\n");
	Attribute *color;
	Structure *structure;
	{
		color = Attribute_create(STRING, "char", "color", NULL);
		
		structure = Structure_create_by_file_path_and_name("structures/cat.h", "Cat");
		Structure_add(structure, Attribute_create(STRING, "char", "name", NULL));
		Structure_add(structure, Attribute_create(PRIMITIVE, "int", "age", NULL));
		Structure_add(structure, color);
		Structure_add(structure, Attribute_create(STRUCTURE_POINTER, "Cat", "next", NULL));
	}
	printf("Structure has structure\'s attributes: %s!\n", Boolean_to_string(Structure_has_structure_attributes(structure)));
	
	char *structure_string_before_delete = Structure_to_string(structure);
	puts("\nStructure before delete:");
	puts(structure_string_before_delete);
	
	Structure_delete(structure, color);
	char *structure_string_after_delete = Structure_to_string(structure);
	puts("\nStructure after delete:");
	puts(structure_string_after_delete);
	
	{
		color = NULL;
		Structure_free(structure);
		free(structure_string_before_delete);
		free(structure_string_after_delete);
	}
	puts("\n");
}


#include "c_structure_serialization/data_types/structure_regular_expressions.h"

void test_data_types_structures_regular_expression() {
	puts("data_types/RegularExpression\n");
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
			{
				puts("          /RegularExpression: to_string");
				char *primitive_string = RegularExpression_to_string(primitive);
				puts(primitive_string);
				free(primitive_string);
				puts("\n");
			}
			{
				puts("          /RegularExpression: RegularExpression_match");
				printf("- Does \"%s\" primitive?\n%s\n", line, (RegularExpression_match(primitive, line)) ? "YES" : "NO");
				puts("\n");
			}
			{
				puts("          /RegularExpression: RegularExpression_parse");
				char **matches = RegularExpression_parse(primitive, line);
				if (matches != NULL) {
					printf("Match #1: \'%s\', match #2: \'%s\'.\n", matches[0], matches[1]);
					free(matches[0]);
					free(matches[1]);
					free(matches);
				} else {
					puts("No Matches!");
				}
				puts("\n");
			}
			{
				free(line);
				RegularExpression_free(primitive);
			}
			puts("\n");
		}
	}
}

size_t code_lines_size = 31;
char *code_lines[] = {
	// primitives
	"	char a;",
	"	unsigned char b;",
	"	byte c;",
	"	short d;",
	"	int e;",
	"	unsigned f;",
	"	long g;",
	"	float h;",
	"	double i;",
	// strings
	"	char *j;",
	"	char k[32];",
	// structures
	"	struct Parrot parrot;",
	"	Cat cat;",
	"	struct Dog*dogA;",
	"	struct Dog *dogB;",
	"	struct Dog* dogC;",
	"	struct Dog * dogD;",
	"	Pet*petA;",
	"	Pet *petB;",
	"	Pet* petC;",
	"	Pet * petD;",
	// arrays
	"	byte***l;",
	"	short***** m;",
	"	int **n;",
	"	unsigned ***** o;",
	"	long p[10][20][30][40];",
	"	float q[8][16][32][3][4][5];",
	"	double****r[1];",
	"	byte****** s[11][22][33][44][55][66];",
	"	short ***t[51][52][53][54];",
	"	int ** u[1][1][2][3];"
	
};

void test_data_types_structures_regular_expressions() {
	puts("data_types/RegularExpressions\n");
	
	RegularExpression *re = structureRegularExpressions->attribute;
	puts("attribute:");
	for (int i=0; i<code_lines_size; i++) {
		Boolean ok = RegularExpression_match(re, code_lines[i]);
		printf("%s - %s\n", code_lines[i], Boolean_to_string(ok));
		if (ok) {
			char **matches = RegularExpression_parse(re, code_lines[i]);
			printf("\'%s\' \'%s\' \'%s\' \'%s\'\n", matches[0], matches[1], matches[2], matches[3]);
			for (int j=0; j<4; j++) {
				free(matches[j]);
			}
			free(matches);
		}
	}
	char *re_string = RegularExpression_to_string(re);
	puts(re_string);
	free(re_string);
	
}

void test_all() {
	test_utils_array();
	test_utils_boolean();
	test_utils_files();
	test_utils_strings();
	test_utils_tabs();
	test_data_types_basic_type();
	test_data_types_dimension();
	test_data_types_attribute();
	test_data_types_structure();
	test_data_types_structures_regular_expression();
	test_data_types_structures_regular_expressions();
}
