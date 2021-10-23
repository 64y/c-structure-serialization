#include "includes.h"


void fwrite_uint32_value30bit_size2bit(FILE *stream, uint32_t value) {
	uint8_t value_size = 0;
	for (uint32_t value_temporary=value<<2; (value_temporary>>8)>0; value_temporary>>=8) {
		value_size = value_size+1;
	}
	value = (value<<2) | value_size;
	value_size = value_size + 1;
	fwrite(&value, value_size, 1, stream);
}

uint32_t fread_uint32_value30bit_size2bit(FILE *stream) {
	uint32_t value=0;
	uint8_t value_size=0;
	fread(&value_size, 1, 1, stream);
	value_size = (value_size&0x03) + 1;
	fseek(stream, -1, SEEK_CUR);
	fread(&value, value_size, 1, stream);
	return value>>2;
}
