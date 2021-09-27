#ifndef DATA_H
#define DATA_H

#include <stddef.h>


typedef unsigned char byte;

typedef struct Data {
	size_t bytes_size;
	byte *bytes;
} Data;

Data * Data_create_by_size(size_t bytes_size);
Data * Data_create_by_data_and_size(byte *bytes, size_t bytes_size);
Data * Data_create_from_string(char *string);
void Data_free(Data *data);
char * Data_to_string(Data *data);

#endif
