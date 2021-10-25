/** @file
@brief Methods to generate source code for json codec. */
#ifndef GENERATE_CODE_FOR_JSON_CODEC_H
#define GENERATE_CODE_FOR_JSON_CODEC_H


#include <stdio.h>

#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"


/** @brief Method generates the declaration of json codec.
@param h_stream A file or a string stream;
@param tabs A pointer for an instance of structure Tabs;
@param structure A pointer for an instance of structure Structure. */
void generate_json_codec_declaration(FILE *h_stream, Tabs *tabs, Structure *structure);

/** @brief Method generates the definition of json codec.
@param c_stream A file or a string stream;
@param tabs A pointer for an instance of structure Tabs;
@param structure A pointer for an instance of structure Structure. */
void generate_json_codec_definition(FILE *h_stream, Tabs *tabs, Structure *structure);


/** @brief Method generates source code to encode primitive for json codec.
@param stream A file or a string stream;
@param tabs A pointer for an instance of structure Tabs;
@param attribute A pointer for an instance of structure Attribute;
@param attribute_pointer A string representation of attribute pointer. */
void json_encode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

/** @brief Method generates source code to encode string for json codec.
@param stream A file or a string stream;
@param tabs A pointer for an instance of structure Tabs;
@param attribute A pointer for an instance of structure Attribute;
@param attribute_pointer A string representation of attribute pointer. */
void json_encode_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

/** @brief Method generates source code to encode structure for json codec.
@param stream A file or a string stream;
@param tabs A pointer for an instance of structure Tabs;
@param attribute A pointer for an instance of structure Attribute;
@param attribute_pointer A string representation of attribute pointer. */
void json_encode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

/** @brief Method generates source code to decode primitive for json codec.
@param stream A file or a string stream;
@param tabs A pointer for an instance of structure Tabs;
@param attribute A pointer for an instance of structure Attribute;
@param attribute_pointer A string representation of attribute pointer. */
void json_decode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

/** @brief Method generates source code to decode string for json codec.
@param stream A file or a string stream;
@param tabs A pointer for an instance of structure Tabs;
@param attribute A pointer for an instance of structure Attribute;
@param attribute_pointer A string representation of attribute pointer. */
void json_decode_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

/** @brief Method generates source code to decode structure for json codec.
@param stream A file or a string stream;
@param tabs A pointer for an instance of structure Tabs;
@param attribute A pointer for an instance of structure Attribute;
@param attribute_pointer A string representation of attribute pointer. */
void json_decode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

/** @brief Method generates source code to decode structure pointer for json codec.
@param stream A file or a string stream;
@param tabs A pointer for an instance of structure Tabs;
@param attribute A pointer for an instance of structure Attribute;
@param attribute_pointer A string representation of attribute pointer. */
void json_decode_structure_pointer(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

#endif
