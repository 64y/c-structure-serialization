#include "c_structure_serialization/utils/program_arguments.h"
#include "c_structure_serialization/generate_source_codes/generate_sources.h"

// conpile total heap usage: 7,967 allocs, 7,967 frees, 9,719,456 bytes allocated
// compile total heap usage: 8,198 allocs, 8,198 frees, 10,667,199 bytes allocated

// example total heap usage: 21,275 allocs, 21,275 frees, 18,621,984 bytes allocated

int main(int argc, char *argv[]) {
	ProgramArguments *programArguments = ProgramArguments_create(argc, argv);
	generate_source_codes_and_library(programArguments);
	{
		ProgramArguments_free(programArguments);
	}
	return 0;
}
