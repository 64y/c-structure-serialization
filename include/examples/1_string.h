#ifndef STRING_H
#define STRING_H

#include <stdio.h>

#include "serialization/registrate.h"
#include "serialization/serialize.h"


#include "structures/parrot.h"

void example_of_structure_with_string_member() {
	puts(" = = = Example of Structure with String Member  = = = ");
	
	Serialize_registrate_structure("Parrot", "structures/parrot.h");
	Serialize *parrot_serialize = Serialize_create("Parrot");
	
	Parrot parrot = {"Tom", 5};
	
	puts("TO_STRING:");
	char *parrot_string = parrot_serialize->to_string(&parrot);
	puts(parrot_string);
	
	{
		Serialize_free(parrot_serialize);
		
		free(parrot_string);
	}
	puts(" = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
}

#endif
