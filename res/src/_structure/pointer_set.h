/** @file
@brief The declaration of structure PointerSet and its methods. */
#ifndef _POINTER_SET_H
#define _POINTER_SET_H


#include "includes.h"


/// A set to store a pointers.
typedef struct PointerSet {
	size_t size; ///< Number of elements in PointerSet.
	Pointer *head; ///< The first element of PointerSet.
	size_t stage; ///< Determine the stage on which the element is added. Not used for now.
	unsigned int address_id_counter; ///< Id value assigns to every added Pointer, which is allows to reenumerate all elements in PointerSet and spends less memory for Pointer address number.
} PointerSet;

/** @brief Creates PointerSet.
@return Created PointerSet. */
PointerSet * PointerSet_create(void);

/** @brief Creates PointerSet and add head as a first element in PointerSet.
@param head A pointer for an instance of structure Pointer.
@return Created PointerSet. */
PointerSet * PointerSet_create_by_head(Pointer *head);

/** @brief Frees memory of PointerSet.
@param pointerSet A pointer for an instance of structure PointerSet. */
void PointerSet_free(PointerSet *pointerSet);

/** @brief Gets string of PointerSet.
@param pointerSet A pointer for an instance of structure PointerSet.
@return A string representation of pointerSet. */
char * PointerSet_to_string(PointerSet *pointerSet);


/** @brief Adds Pointer into PointerSet.
@param pointerSet A pointer for an instance of structure PointerSet;
@param pointer A pointer for an instance of structure Pointer.
@return True if Pointer added successfully or False if such a Pointer already presents in PointerSet. */
bool PointerSet_add(PointerSet *pointerSet, Pointer *pointer);

/** @brief Gets Poinger from PointerSet by hashCode.
@param pointerSet A pointer for an instance of structure PointerSet.
@param hashCode A pointer's hashCode.
@return A pointer for an instance of structure Pointer or NULL. */
Pointer * PointerSet_get_by_hashCode(PointerSet *pointerSet, char *hashCode);

/** @brief Checks PointerSet for Poinger with hashCode.
@param pointerSet A pointer for an instance of structure PointerSet.
@param hashCode A pointer's hashCode.
@return True if Pointer presents of False otherwise. */
bool PointerSet_contains_by_hashCode(PointerSet *pointerSet, char *hashCode);

/** @brief
@param pointerSet A pointer for an instance of structure PointerSet.
@param hashCode A pointer's hashCode.
@return A pointer for an instance of structure Pointer or NULL. */
Pointer * PointerSet_remove_by_hashCode(PointerSet *pointerSet, char *hashCode);

/** @brief Increases value of stage.
@param pointerSet A pointer for an instance of structure PointerSet. */
void PointerSet_stage_next(PointerSet *pointerSet);

#endif
