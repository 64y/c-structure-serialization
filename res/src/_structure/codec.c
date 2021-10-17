#include "includes.h"


void walk_through(PointerSet *pointerSet) {
	size_t curr_i=0, curr_size=PointerSet_size(pointerSet);
	for (Pointer *curr=pointerSet->head; curr!=NULL; curr=curr->next, curr_size=PointerSet_size(pointerSet), PointerSet_stage_next(pointerSet)) {
		while (curr_i<curr_size && curr!=NULL) {
			structures_methods[curr->name][WALK_POINTER](pointerSet, pointer);
			curr = curr->next;
			curr_i = curr_i + 1;
		}
	}
}

Data * encode(StructureMethod structureMethod, Pointer *pointer) {
	Data *structure_data = Data_create_null();
	{
		FILE *structure_byte_stream = open_memstream((char **)&structure_data->bytes, &structure_data->bytes_size);
		PointerSet *pointerSet = PointerSet_create_by_head(pointer);
		walk_through(pointerSet);
		for (Pointer *curr = pointerSet->head; curr!=NULL; curr=curr->next) {
			structures_methods[curr->name][structureMethod](structure_byte_stream, pointerSet, curr);
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
			structures_methods[curr->name][structureMethod](structure_byte_stream, pointerSet, curr);
		}
		structure = pointerSet->head->pointer;
		{
			fclose(structure_byte_stream);
			PointerSet_free(pointerSet);
		}
	}
	return structure;
}
