#ifndef STRING_H
#define STRING_H

#include <stdio.h>

#include <c_structure_serialization/serializer.h>


#include "structures/parrot.h"

void example_of_structure_with_string_member() {
	puts(" = = = Example of Structure with String Member  = = = ");
	
	Serializer *parrot_serializer = Serializer_create("Parrot");
	
	Parrot parrot = {"Tom", 5};
	
	puts("TO_STRING:");
	char *parrot_string = parrot_serializer->to_string(&parrot);
	puts(parrot_string);
	
	{
		Serializer_free(parrot_serializer);
		
		free(parrot_string);
	}
	puts(" = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
}

#endif
