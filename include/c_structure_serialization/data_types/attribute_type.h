/** @file
@brief AttributeType enum is declared here. */
#ifndef ATTRIBUTE_TYPE
#define ATTRIBUTE_TYPE


#include <stddef.h>


/** @brief Determine the acseptable types of structure's Attribute.
@details A enum declared types for primitives, string, structures, pointers of structures and their array versions. */
typedef enum AttributeType {
	NO_TYPE, ///< No type. If the variable in line of structure code was determined as an attribute with no type, then the program should stops.
	PRIMITIVE, ///< Primitive type: char, unsigned char, byte, short, int, unsigned, long, float, double. 
	STRING, ///< String type: char *.
	STRUCTURE, ///< The structure.
	STRUCTURE_POINTER, ///< The pointer of structure.
	PRIMITIVE_ARRAY, ///< An array of primitives.
	STRING_ARRAY, ///< An array of string. If string matrix with static dimensions has no sizes attributes, then it determines as an array of primitive.
	STRUCTURE_ARRAY, ///< An array of structures.
	STRUCTURE_POINTER_ARRAY ///< An array of structures pointers.
} AttributeType;

/// Size of ATTRIBUTE_TYPE_STRING.
extern const size_t ATTRIBUTE_TYPE_STRING_SIZE;

/// A string representations of AttributeType elements.
extern const char *ATTRIBUTE_TYPE_STRING[];

#endif
