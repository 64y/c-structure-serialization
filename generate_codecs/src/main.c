#include "serialization/generate_library.h"


int main(int argc, char *argv[]) {
	generate_libraries(argv[1], argv[2]);
	return 0;
}
