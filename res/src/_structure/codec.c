#include <stdio.h>
#include <stdlib.h>

#include "_structure/structure_info.h"
#include "_structure/pointer.h"
#include "_utils/data.h"
#include "_structure/codec.h"


Data * encode(StructureMethod structureMethod, Pointer *pointer) {
	Data *structure_data = Data_create_null();
	{
		FILE *structure_byte_stream = open_memstream((char **)&structure_data->bytes, &structure_data->bytes_size);
		PointerSet *pointerSet = PointerSet_create_by_head(pointer);
		for (Pointer *curr = pointerSet->head; curr!=NULL; curr=curr->next) {
			structures_methods[structureMethod][curr->name](structure_byte_stream, pointerSet, curr);
		}
		{
			fclose(structure_byte_stream);
			PointerSet_free(pointerSet);
		}
	}
	return structure_data;
}

void * decode(StructureMethod structureMethod, Pointer *pointer, Data *structure_data) {
	void *structure = NULL;
	{
		FILE *structure_byte_stream = fmemopen(structure_data->bytes, structure_data->bytes_size, "rb");
		PointerSet *pointerSet = PointerSet_create_by_head(pointer);
		for (Pointer *curr = pointerSet->head; curr!=NULL; curr=curr->next) {
			structures_methods[structureMethod][curr->name](structure_byte_stream, pointerSet, curr);
		}
		structure = pointerSet->head->pointer;
		{
			fclose(structure_byte_stream);
			PointerSet_free(pointerSet);
		}
	}
	return structure;
}
