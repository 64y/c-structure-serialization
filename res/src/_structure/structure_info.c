#include "includes.h"


const size_t STRUCTURE_NAME_SIZE = %d;
const char *STRUCTURE_NAME_STRING[] = {
	%s
};

void (*structures_methods[][6]) (FILE *structure_codec_stream, PointerSet *pointerSet, Pointer *pointer) = %s;