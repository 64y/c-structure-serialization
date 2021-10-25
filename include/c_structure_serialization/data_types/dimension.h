/** @file
@brief The declaration of Dimension structure and its methods. */
#ifndef DIMENSION_H
#define DIMENSION_H


#include <stddef.h>


/** @brief The Dimension for any Attribute of Structure.
@details Dimension structure contains the number of static and dynamic dimensions, and their sizes or names with Structure shortcut for each Attribute of Structure. Each Attribute has Dimension structure variablie. Its value is NULL if AttributeType of its Attribute not _ARRAY. */
typedef struct Dimension {
	size_t size; ///< Total size. The sum of static and dynamic sizes. The size of dimensions array.
	size_t static_size; ///< Static size. Number of dimensions defined by [].
	size_t static_size_source; ///< The source static size.
	size_t dynamic_size; ///< Dynamic size. Number of dimensions defined by *.
	size_t dynamic_size_source; ///< The source dynamic size.
	char **dimensions; ///< The array for Attribute Dimension. Each value is a string contains: number (example 50) if it is a static dimension or shortcut and dimension name for Attribute (_array->arr_0) if it is a dynamic dimension.
} Dimension;


/** @brief Creates Dimension.
@details Method creates an instance of structure Dimension by static and dynamic sizes.
@param static_size Static size;
@param dynamic_size Dynamic size.
@return Created Dimension. */
Dimension * Dimension_create(size_t static_size, size_t dynamic_size);

/** @brief Frees memory of Dimension.
@details Method assigns a zero value for size variables and frees size strings in dimensions array, dimensions array itself and an instance of structure Dimension and assigns a NULL value.
@param dimension A pointer to instance of structure Dimension.*/
void Dimension_free(Dimension *dimension);

/** @brief Gets string of Dimension.
@details Method creates a string representation for an instance of structure Dimension.
@param dimension A pointer to instance of structure Dimension.
@return A string representation of structure Dimension. */
char * Dimension_to_string(Dimension *dimension);


/** @brief Sets a new value in Dimension.
@details Method replaces a index string in dimensions array with new value.
@param dimension A pointer to instance of structure Dimension;
@param index An index of dimension in dimensions array;
@param value New value.*/
void Dimension_set_dimension(Dimension *dimension, int index, char *value);

#endif
