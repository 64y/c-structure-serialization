#include "examples/0_primitives.h"
#include "examples/1_string.h"
#include "examples/2_array.h"
#include "examples/3_matrices.h"
#include "examples/4_structures.h"
#include "examples/5_matrices_of_structures.h"


int main(int argc, char *argv[]) {
	int DO_FLAGS = DO_TO_STRING | DO_JSON_ENCODE | DO_JSON_DECODE | DO_BYTES_ENCODE | DO_BYTES_DECODE;
	size_t examples_size = 8;
	void (*examples[]) (int DO_FLAGS) = {example_of_structure_with_primitives_members, example_of_structure_with_string_member, example_of_structure_with_array, example_of_structure_with_matrix, example_of_structure_with_matrices, example_of_structure_with_matrices_of_strings, example_of_structure_with_structures_and_structures_pointers, example_of_structure_with_matrices_of_structures};
	for (int i=0; i<examples_size; i++) {
		examples[i](DO_FLAGS);
	}
	return 0;
}
