#include <stdio.h>
#include <stdlib.h>

#include <c_structure_serialization/serializer.h>


#include "structures/all_primitives.h"


int main(int argc, char *argv[]) {
	puts(" = = = Example of Structure with Primitives Members = = = ");
	
	Serializer *all_primitives_serializer = Serializer_create("AllPrimitives");
	
	AllPrimitives allPrimitives = {'D', 0xFF, 0x00, 1, 2, 3l, 4.0f, 5.5};
	
	puts("TO_STRING");
	char *allPrimitives_string = all_primitives_serializer->to_string(&allPrimitives);
	puts(allPrimitives_string);
	
	{
		Serializer_free(all_primitives_serializer);
		
		free(allPrimitives_string);
	}
	puts(" = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");
	return 0;
}

