#ifndef $0_PRIMITIVES_H
#define $0_PRIMITIVES_H

#include <stdio.h>
#include <stdlib.h>

#include <c_structure_serialization/serializer.h>


#include "structures/all_primitives.h"

void example_of_structure_with_primitives_members() {
	puts(" = = = Example of Structure with Primitives Members = = = ");
	
	Serializer *all_primitives_serializer = Serializer_create("./my_lib", "AllPrimitives");
	
	AllPrimitives allPrimitives = {'D', 0xFF, 0x00, 1, 2, 3l, 4.0f, 5.5};
	
	puts("TO_STRING");
	char *allPrimitives_string = all_primitives_serializer->to_string(&allPrimitives);
	puts(allPrimitives_string);
	
	{
		Serializer_free(all_primitives_serializer);
		free(allPrimitives_string);
	}
	puts(" = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");
}

#endif
