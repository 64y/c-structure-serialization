#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>

#include "_utils/data.h"

#define JSON_LENGTH_MAX 2048

char * base64_encode(Data *data);
Data * base64_decode(char *data_base64_code);

char * base64_encode_string(char *string);
char * base64_decode_string(char *string_base64_code);

#endif
