#ifndef DIMENSION_H
#define DIMENSION_H


#include <stddef.h>


typedef struct Dimension {
	size_t size;
	size_t static_size;
	size_t static_size_source;
	size_t dynamic_size;
	size_t dynamic_size_source;
	char **dimensions;
} Dimension;

Dimension * Dimension_create(size_t static_size, size_t dynamic_size);
void Dimension_free(Dimension *dimension);
char * Dimension_to_string(Dimension *dimension);

void Dimension_set_dimension(Dimension *dimension, int index, char *value);

#endif
