/** @file
@brief Base64 algorithm. */
#ifndef _UTILS_BASE64_H
#define _UTILS_BASE64_H

#include <stddef.h>

#include "_utils/data.h"


#define BASE64_LENGTH_MAX 65536


/** @brief Method encodes data into base64 string.
@param data An instance of structure Data.
@return A base64 string of data. */
char * base64_encode(Data *data);

/** @brief Methods decodes base64 string into data.
@param data_base64_code A base64 string.
@return A decoded instance of structure Data. */
Data * base64_decode(char *data_base64_code);


/** @brief Method encodes string into base64 string.
@param string A source string.
@return Base64 representation of string*/
char * base64_encode_string(char *string);

/** @brief Method decodes base64 string into string.
@param string_base64_code A base64 string.
@return A source string. */
char * base64_decode_string(char *string_base64_code);

#endif
