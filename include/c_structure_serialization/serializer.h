/** @file
@brief The declaration of Serializer structure and its methods. */
#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "c_structure_serialization/utils/data.h"


/** @brief A codecs methods for Structure.
@details */
typedef struct Serializer {
	void *handle; ///< A pointer for opaque handle of a dynamic library file.
	char * (*to_string) (void *structure); ///< A pointer to method to_string.
	char * (*json_encode) (void *structure); ///< A pointer to method json_encode.
	void * (*json_decode) (char *structure_json); ///< A pointer to method json_decode.
	Data * (*byte_encode) (void *structure); ///< A pointer to method byte_encode.
	void * (*byte_decode) (Data *structure_bytes); ///< A pointer to method byte_decode.
} Serializer;


/** @brief Creates Serializer.
@details Method opens dynamic library file with path library_path and loads codecs methods from this file.
@param library_path The path of library.
@param structure_name The name of Structure. One library is able to store codecs for several structures.
@return Created Serializer. */
Serializer * Serializer_create(char *library_path, char *structure_name);

/** @brief Frees memory of Serializer.
@details Methods closes and frees opaque handle and frees an instance of structure Serializer and assigns a NULL value.
@param serializer A pointer to instance of structure Serializer.*/
void Serializer_free(Serializer *serializer);

#endif
