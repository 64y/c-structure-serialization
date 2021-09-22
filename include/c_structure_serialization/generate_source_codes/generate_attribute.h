#ifndef GENERATE_ATTRIBUTE_H
#define GENERATE_ATTRIBUTE_H


#include "c_structure_serialization/utils/boolean.h"
#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"


char * generate_attribute_pointer(Structure *structure, Attribute *attribute);
char * generate_attribute_with_loop(Structure *structure, Attribute *attribute, Tabs *tabs, Boolean slash_n);

#endif
