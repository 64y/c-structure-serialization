#ifndef _WRITE_READ_UINT32_H
#define _WRITE_READ_UINT32_H

#include <stdint.h>
#include <stdio.h>


void fwrite_uint32_value30bit_size2bit(FILE *stream, uint32_t value);
uint32_t fread_uint32_value30bit_size2bit(FILE *stream);

#endif
