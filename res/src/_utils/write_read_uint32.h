/** @file
@brief Methods to write/read uint32 value.
@details Methods to write/read an uint32 value in/from file. There the uint32 has 30 bits for value and 2 bits for size of value. It used to write/read lengths of strings and addresses of pointers, which is allowes to save memory space. */
#ifndef _WRITE_READ_UINT32_H
#define _WRITE_READ_UINT32_H

#include <stdint.h>
#include <stdio.h>


/** @brief Method writes uint32 value into file or string stream.
@param stream An opened stream;
@param value A value to write. */
void fwrite_uint32_value30bit_size2bit(FILE *stream, uint32_t value);

/** @brief Method reads uint32 value from file or string stream.
@param stream An opened stream;
@return A value readed from stream. */
uint32_t fread_uint32_value30bit_size2bit(FILE *stream);

#endif
