/** @file
@brief BasicType structure describes a primitive types. */
#ifndef DATA_TYPE_H
#define DATA_TYPE_H


#include <stddef.h>


/** @brief A primitive type description.
@details BasicType structure describes primitive type by its name, sizeof primitive in bytes, format specifier and format parameters.s */
typedef struct BasicType {
	char *name; ///< Name of primitive type.
	size_t size_in_bytes; ///< Size of primitive in bytes.
	char *format_specifier; ///< Primitive format specifier.
	char *format_parameters; ///< Primitive format parameters. It is not used for now.
} BasicType;

/** @brief Gets string of BasicType.
@details Method creates a string representation for an instance of structure BasicType.
@param basicType A pointer to instance of structure BasicType.
@return A string representation of BasicType. */
char * BasicType_to_string(BasicType *basicType);

/// Total number of primitive types, a size of BASIC_TYPE array.
extern const size_t BASIC_TYPE_SIZE;

/// An array of predefined primitive types.
extern BasicType BASIC_TYPE[];

/** @brief 
@details 
@param name A string name of primitive type.
@return If BasicType with name exists then returns structure pointer else returns NULL otherwise. */
BasicType * BasicType_get_by_name(char *name);

#endif
