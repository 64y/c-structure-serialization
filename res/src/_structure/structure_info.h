/** @file
@brief An information about structures in source code for dynamic library file. */
#ifndef _STRUCTURE_INFO_H
#define _STRUCTURE_INFO_H


#include "includes.h"


/// Number of structure. Size of STRUCTURE_NAME_STRING array.
extern const size_t STRUCTURE_NAME_SIZE;

/// Enumeration of all structures.
typedef enum {
	%s
} StructureName;

/// String representation of each element in StructureName enum.
extern const char *STRUCTURE_NAME_STRING[];


/// Enumeration for codecs methods.
typedef enum StructureMethod {
	TO_STRING, ///< to_string method
	JSON_ENCODE, ///< json_encode method
	JSON_DECODE, ///< json_decode method
	BYTE_ENCODE, ///< byte_encode method
	BYTE_DECODE ///< byte_decode method
} StructureMethod;

#endif
