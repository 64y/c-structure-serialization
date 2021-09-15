#include <stdio.h>
#include <stdlib.h>

#include "utils/basic_defines.h"
#include "data_types/dimension.h"


Dimension * Dimension_create(size_t static_size, size_t dynamic_size) {
	 Dimension *dimension = (Dimension *)malloc(sizeof(Dimension));
	 dimension->size = static_size + dynamic_size;
	 dimension->static_size = static_size;
	 dimension->dynamic_size = dynamic_size;
	 dimension->dimensions = (char **)calloc(dimension->size, sizeof(char *));
	 return dimension;
}

void Dimension_free(Dimension *dimension) {
	if (dimension != NULL) {
		if (dimension->dimensions != NULL) {
			for (int i=0; i<dimension->size; i++) {
				if (dimension->dimensions[i]!=NULL) {
					free(dimension->dimensions[i]);
					dimension->dimensions[i] = NULL;
				}
			}
			free(dimension->dimensions);
			dimension->dimensions = NULL;
		}
		dimension->size = 0;
		dimension->static_size = 0;
		dimension->dynamic_size = 0;
		free(dimension);
		dimension = NULL;
	}
}

char * Dimension_to_string(Dimension *dimension) {
	if (dimension == NULL) {
		return string_copy("No Dimensions");
	}
	char *dimension_string;
	{
		size_t dimension_string_length;
		FILE *dimension_string_stream = open_memstream(&dimension_string, &dimension_string_length);
		fprintf(dimension_string_stream, "Dimension: [size=static_size+dynamic_size] ~ [%ld=%ld+%ld], ", dimension->size, dimension->static_size, dimension->dynamic_size);
		fprintf(dimension_string_stream, "dimensions: [");
		for (int i=0; i<dimension->size; i++) {
			fprintf(dimension_string_stream, "%s%s", dimension->dimensions[i], (i<dimension->size-1) ? ", " : "");
		}
		fprintf(dimension_string_stream, "]");
		fclose(dimension_string_stream);
	}
	return dimension_string;
}

void Dimension_set_dimension(Dimension *dimension, int index, char *value) {
	if (dimension->dimensions[index] != NULL) {
		free(dimension->dimensions[index]);
	}
	dimension->dimensions[index] = string_copy(value);
}
