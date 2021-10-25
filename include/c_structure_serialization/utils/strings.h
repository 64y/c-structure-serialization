/** @file
@brief Utils methods to work with strings. */
#ifndef STRINGS_H
#define STRINGS_H


#include <stdarg.h>
#include <stdbool.h>

#include "c_structure_serialization/utils/array.h"


#define NO_MORE_STRINGS NULL


/** @brief Creates a new string.
@details Method creates a new variable of type char *, allocates strlen(string)+1 elements of char for it and copies a string to it.
@param string A source string.
@return A created string. */
char * string_create(char *string);

/** @brief Creates a new string by format string and arguments.
@details Method creates a new variable of type char *, file stream for it of type FILE *, uses a vfprintf method to create a formated string and close string stream after all.
@param format A format string;
@param ... The arguments of format string.
@return A resulted string. */
char * string_create_by_format(char *format, ...);

/** @brief Frees memory for string.
@details Methods frees the allocated memory for string and assigned a NULL value.
@param string A source string. */
void string_free(char *string);


/** @brief Compares two strings.
@details Methods compares stringA and stringB by using a strcmp method, and if it return zero value the method returns True.
@param stringA A first string;
@param stringB A second string.
@return True if strings are equals or False otherwise. */
bool string_equals(char *stringA, char *stringB);

/** @brief Examines string for specific ending.
@details Methods return True, if string ends with end. False otherwise.
@param string A source string;
@param end A string ending.
@return True if string ends with end or False otherwise. */
bool string_ends_with(char *string, char *end);

/** @brief Copies string.
@details Method creates a new variable of type char *, allocates strlen(string)+1 elements of char for it and copies a string to it.
@param string A source string.
@return A created string. */
char * string_copy(char *string);

/** @brief String lower case.
@details Method creates a new variable of type char *, allocates strlen(string)+1 elements of char for it and copies lower case of each char of string.
@param string A source string.
@return A resulted string. */
char * string_to_lower(char *string);

/** @brief String upper case.
@details Method creates a new variable of type char *, allocates strlen(string)+1 elements of char for it and copies upper case of each char of string.
@param string A source string.
@return A resulted string. */
char * string_to_upper(char *string);

/** @brief Replaces char in string.
@details Method replaces each entry of symbol find with symbol replace.
@param string A source string;
@param find A char to be find;
@param raplace A char to replace with.
@return A resulted string. */
char * string_replace_char(char *string, char find, char replace);

/** @brief Concatenates strings.
@details Methods concatenates first string with other strings.
@param first_string A first source string;
@param ... Other strings, and NULL - is the last one.
@return A resulted string. */
char * string_appends(char *first_string, ...);


/** @brief Makes a shortcut for structure's name.
@details Mathod makes makes a shortcut for structure's name: add a '_' symbol to the start of string and lower the first symbol of string.
@param string A source string.
@return A shortcut of string. */
char * string_make_shortcut(char *string);

/** @brief Makes stars to pointers.
@details Method creates a string with space and times stars, or empty string if times equals to zero.
@param times Number of stars.
@return A string with times stars. */
char * string_repeat_star(size_t times);

/** @brief Array's create method for strings. */
void * array_string_create(va_list string_arguments);
/** @brief Array's free method for strings. */
void array_string_free(void *string);
/** @brief Array's to_string method for strings. */
char * array_string_to_string(void *string);
/** @brief Comparator method for strings. */
int array_string_cmp(const void *a, const void *b);
/** @brief Creates an Array for strings. */
Array * Array_create_for_string();

#endif
