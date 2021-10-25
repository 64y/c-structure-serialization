/**@file
@brief The declaration of byte data type and Data structure and methods to work with this structure. */
#ifndef UTILS_DATA_H
#define UTILS_DATA_H


#include <stddef.h>


/// A single byte.
typedef unsigned char byte;

/// A structure contains the size of byte array and byte array itself.
typedef struct Data {
	size_t bytes_size; ///< The size of byte array.
	byte *bytes; ///< Byte array.
} Data;

/** @brief Creates uninitialized Data.
@details Method creates an instance of structure Data with bytes_size assigned to 0 and bytes assigned to NULL.
@return Created instance of structure Data. */
Data * Data_create_null(void);

/** @brief Creates Data by size.
@details Method creates an instance of structure Data, which byte array size is assigned to bytes_size.
@param bytes_size Size of byte array.
@return Created instance of structure Data. */
Data * Data_create_by_size(size_t bytes_size);

/** @brief Creates Data by bytes_size and bytes.
@details Method creates an instance of structure Data, which byte array is a copy of bytes and size of byte array is assigned to bytes_size.
@param bytes Byte array;
@param bytes_size Size of byte array.
@return Created instance of structure Data. */
Data * Data_create_by_data_and_size(byte *bytes, size_t bytes_size);

/** @brief Creates Data from string.
@details Method create san instance of structure Data, which byte array is a copy of chars from string and size of byte array is assigned to strlen(string).
@param string A source string.
@return Created instance of structure Data. */
Data * Data_create_from_string(char *string);

/** @brief Frees memory of Data.
@details Method frees the allocated memory for an instance of structure Data: size of byte array bytes_size is assigned to zero, frees byte array bytes and assigned a NULL value, frees an instance of structure Data data and assigned a NULL value.
@param data A pointer to an instance of structure Data.*/
void Data_free(Data *data);

/** @brief Gets string of Data.
@details Method creates a string representation for an instance of structure Data.
@param data A pointer to an instance of structure Data.
@returns A string representation of Data. */
char * Data_to_string(Data *data);

#endif
