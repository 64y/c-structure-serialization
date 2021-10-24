#include "c_structure_serialization/utils/program_arguments.h"
#include "c_structure_serialization/generate_source_codes/generate_sources.h"

int main(int argc, char *argv[]) {
	ProgramArguments *programArguments = ProgramArguments_create(argc, argv);
	generate_source_codes_and_library(programArguments);
	{
		ProgramArguments_free(programArguments);
	}
	return 0;
}
