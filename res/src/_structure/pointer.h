/** @file
@brief The declaration of structure Pointer and its methods. */
#ifndef _POINTER_H
#define _POINTER_H


#include "includes.h"


/// Pointer structure
typedef struct Pointer {
	StructureName name; ///< StructureName of structure.
	void *pointer; ///< A pointer for structure.
	long address; ///< A structure's address.
	unsigned int address_id; ///< A structure's address id. It assigns when added to the PointerSet and helps to reduce sizeof pointer address.
	char *hashCode; ///< A hashCode of structure (StructureName@@Address).
	struct Pointer *next; ///< A pointer to the next element in PointerSet.
} Pointer;

/** @brief Creates Pointer by name and pointer to structure.
@param name StructureName of structure;
@param structure A pointer for structure.
@return Created Pointer. */
Pointer * Pointer_create_by_name_pointer(StructureName name, void *structure);

/** @brief Creates Pointer by name, pointer to structure and pointer address.
@param name StructureName of structure;
@param structure A pointer for structure;
@param address A structure's address.
@return Created Pointer. */
Pointer * Pointer_create_by_name_pointer_address(StructureName name, void *structure, long address);

/** @brief Creates Pointer by name, pointer to structure and pointer hashCode.
@param name StructureName of structure;
@param structure A pointer for structure;
@param hashCode A structure's hashCode.
@return Created Pointer. */
Pointer * Pointer_create_by_name_pointer_hashCode(StructureName name, void *structure, char *hashCode);

/** @brief Frees memory of Pointer.
@param pointer A pointer for an instance of structure Pointer. */
void Pointer_free(Pointer *pointer);

/** @brief Gets string of Pointer.
@param pointer A pointer for an instance of structure Pointer. 
@return String representation of Pointer. */
char * Pointer_to_string(Pointer *pointer);

#endif
