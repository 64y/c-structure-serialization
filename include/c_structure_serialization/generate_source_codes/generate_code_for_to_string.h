/** @file
@brief Methods to generate source code for to_string method. */
#ifndef GENERATE_CODE_FOR_TO_STRING_H
#define GENERATE_CODE_FOR_TO_STRING_H


#include <stdio.h>

#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"


/** @brief Method generates the declaration of to_string method.
@param h_stream A file or a string stream;
@param tabs A pointer for an instance of structure Tabs;
@param structure A pointer for an instance of structure Structure. */
void generate_to_string_declaration(FILE *h_stream, Tabs *tabs, Structure *structure);

/** @brief Method generates the definition of to_string method.
@param c_stream A file or a string stream;
@param tabs A pointer for an instance of structure Tabs;
@param structure A pointer for an instance of structure Structure. */
void generate_to_string_definition(FILE *c_stream, Tabs *tabs, Structure *structure);


/** @brief Method generates source code to encode primitive for to_string method.
@param stream A file or a string stream;
@param tabs A pointer for an instance of structure Tabs;
@param attribute A pointer for an instance of structure Attribute;
@param attribute_pointer A string representation of attribute pointer. */
void to_string_encode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

/** @brief Method generates source code to encode string for to_string method.
@param stream A file or a string stream;
@param tabs A pointer for an instance of structure Tabs;
@param attribute A pointer for an instance of structure Attribute;
@param attribute_pointer A string representation of attribute pointer. */
void to_string_encode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

#endif
