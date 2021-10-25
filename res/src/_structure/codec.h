/** @file
@brief The declaration of basic codec methods. */
#ifndef _CODEC_H
#define _CODEC_H


#include "includes.h"


/** @brief Encode method.
@param structureMethod The encoded codec method;
@param pointer A pointer for an instance of structure Pointer.
@return Encoded instance of structure Data. */
Data * encode(StructureMethod structureMethod, Pointer *pointer);

/** @brief Decode method.
@param structureMethod The decoded codec method;
@param pointer A pointer for an instance of structure Pointer.
@param structure_data A pointer for an instance of structure Data.
@return Decoded pointer of source structure. */
void * decode(StructureMethod structureMethod, Pointer *pointer, Data *structure_data);

#endif
