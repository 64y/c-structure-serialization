#ifndef _UTILS_BASE64_H
#define _UTILS_BASE64_H

#include <stddef.h>

#include "_utils/data.h"


#define BASE64_LENGTH_MAX 65536


char * base64_encode(Data *data);
Data * base64_decode(char *data_base64_code);

char * base64_encode_string(char *string);
char * base64_decode_string(char *string_base64_code);

#endif
