#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_structure_serialization/utils/data.h"

Data * Data_create_null(void) {
	Data *data = (Data *)malloc(sizeof(Data));
	data->bytes_size = 0;
	data->bytes = NULL;
	return data;
}

Data * Data_create_by_size(size_t bytes_size) {
	Data *data = (Data *)malloc(sizeof(Data));
	data->bytes_size = bytes_size;
	data->bytes = (byte *)calloc(data->bytes_size, sizeof(byte));
	return data;
}

Data * Data_create_by_data_and_size(byte *bytes, size_t bytes_size) {
	Data *data = Data_create_by_size(bytes_size);
	memcpy(data->bytes, bytes, bytes_size);
	return data;
}

Data * Data_create_from_string(char *string) {
	Data *data = Data_create_by_data_and_size((byte *)string, strlen(string));
	return data;
}

void Data_free(Data *data) {
	if (data != NULL) {
		if (data->bytes!=NULL) {
			free(data->bytes);
			data->bytes = NULL;
		}
		data->bytes_size = 0;
		free(data);
		data = NULL;
	}
}

char * Data_to_string(Data *data) {
	char *data_string;
	{
		size_t data_string_length;
		FILE *data_string_stream = open_memstream(&data_string, &data_string_length);
		fprintf(
			data_string_stream,
			"Data @%lx:\n"
			"bytes_size: \'%ld\';\n"
			"bytes: \'",
			(long)(void *)data, data->bytes_size
		);
		for (int i=0; i<data->bytes_size; i++) {
			fprintf(data_string_stream, "%c", (isprint(data->bytes[i]))?data->bytes[i]:'.');
		}
		fprintf(data_string_stream, "\'.");
		{
			fclose(data_string_stream);
		}
	}
	return data_string;
}
