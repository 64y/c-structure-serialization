#ifndef BASIC_DEFINES_H
#define BASIC_DEFINES_H

#include <stdlib.h>

#define error(ERROR_MESSAGE)\
	fprintf(stderr, "ERROR [%s:%d]: to %s\n", __FILE__, __LINE__, ERROR_MESSAGE);\
	exit(-1);


typedef unsigned char byte;


typedef enum {
	false,
	true
} Boolean;

char * Boolean_to_string(Boolean bool);


char * string_copy(char *string);
Boolean string_equals(char *string0, char *string1);
char * string_to_lower(char *string);
char * string_to_upper(char *string);
char * string_make_shortcut(char *string);
char * string_appends(char *strings[]);
char * string_random(size_t string_length_min, size_t string_length_max);


void file_write(char *path, char *source_code);
char * file_read(char *path);

char * path_get_dir(char *path);

#endif
