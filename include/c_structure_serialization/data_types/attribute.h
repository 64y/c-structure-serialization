/** @file
@brief The declaration of Attribute structure and its methods. */
#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H


#include "c_structure_serialization/data_types/attribute_type.h"
#include "c_structure_serialization/data_types/dimension.h"


/** @brief A description of Structure's variable.
@details Attribute structure describes each attribute in Structure by AttributeType, string of data type, string of variable name, Dimension and pointer to the next Attribute in Structure. */
typedef struct Attribute {
	AttributeType type; ///< The AttributeType of Attribute.
	char *data_type; ///< The name of data type.
	char *data_type_upper; ///< The upper name of data type. Used for structures attributes only.
	char *name; ///< Variable name.
	Dimension *dimension; ///< Variable dimension. If variable is not any kind of array, then it is a NULL.
	struct Attribute *next; ///< The pointer to the next instance of structure Attribute in Structure.
} Attribute;


/** @brief Creates Attribute.
@details Creates structure Attribute with help of method arguments.
@param type The AttributeType of variable;
@param data_type The data type name of variable;
@param name The name of variable;
@param dimension The variable dimension.
@return Created Attribute. */
Attribute * Attribute_create(AttributeType type, char *data_type, char *name, Dimension *dimension);

/** @brief Frees memory of Attribute.
@details Methods frees allocated memory for strings data_type, data_type_upper, name; calls Dimension_free method to free the dimension, assignes a NULL value to next and frees an instance of structure Attribute and assigns a NULl value to attribute.
@param attribute A pointer to instance of structure Attribute.*/
void Attribute_free(Attribute *attribute);

/** @brief Gets string of Attribute.
@details Method creates a string representation for an instance of structure Attribute.
@param attribute A pointer to instance of structure Attribute.
@return A string representation of Attribute. */
char * Attribute_to_string(Attribute *attribute);

#endif
