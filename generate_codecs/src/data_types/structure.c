#include <stdlib.h>
#include <string.h>

#include "utils/basic_defines.h"
#include "data_types/structure.h"


Structure * Structure_create(char *name, char *file_name) {
	Structure *structure = (Structure *)malloc(sizeof(Structure));
	structure->file_name = string_copy(file_name);
	structure->name = string_copy(name);
	structure->shortcut = string_make_shortcut(structure->name);
	structure->size = 0;
	structure->head = NULL;
	return structure;
}

void Structure_free(Structure *structure) {
	if (structure != NULL) {
		if (structure->file_name != NULL) {
			free(structure->file_name);
			structure->file_name = NULL;
		}
		if (structure->name != NULL) {
			free(structure->name);
			structure->name = NULL;
		}
		if (structure->shortcut != NULL) {
			free(structure->shortcut);
			structure->shortcut = NULL;
		}
		for (Attribute *curr=structure->head; structure->head!=NULL; curr=structure->head) {
			structure->head = structure->head->next;
			Attribute_free(curr);
		}
		free(structure);
		structure = NULL;
	}
}

char * Structure_to_string(Structure *structure) {
	char *structure_string;
	{
		size_t structure_string_length;
		FILE *structure_string_stream = open_memstream(&structure_string, &structure_string_length);
		fprintf(structure_string_stream, "Structure \'%s\' [%s] (%s) has %ld attributes%s\n", structure->name, structure->file_name,  structure->shortcut, structure->size, (structure->size==0)?".":":\n");
		for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
			char *attribute_string = Attribute_to_string(curr);
			fprintf(structure_string_stream, "%s\n", attribute_string);
			free(attribute_string);
		}
		fprintf(structure_string_stream, "Structure \'%s\' end.", structure->name);
		fclose(structure_string_stream);
	}
	return structure_string;
}

void Structure_add(Structure *structure, Attribute *attribute) {
	if (structure->head == NULL) {
		structure->size = 1;
		structure->head = attribute;
	} else {
		Attribute *curr = structure->head;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		structure->size = structure->size + 1;
		curr->next = attribute;
	}
}

int Structure_delete(Structure *structure, Attribute *attribute) {
	if (structure->head==NULL || attribute==NULL) {
		return false;
	}
	if (structure->head == attribute) {
		Attribute *curr = structure->head;
		structure->head = structure->head->next;
		curr->next = NULL;
		Attribute_free(curr);
		structure->size = structure->size - 1;
		return true;
	} else {
		for (Attribute *prev = structure->head, *curr=structure->head->next; prev!=NULL && curr!=NULL; prev=prev->next, curr=curr->next) {
			if (curr == attribute) {
				prev->next = curr->next;
				curr->next = NULL;
				Attribute_free(curr);
				structure->size = structure->size - 1;
				break;
			}
		}
		return true;
	}
	return false;
}

int Structure_has_structure_attributes(Structure *structure) {
	int has = 0;
	for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
		has |= curr->type==STRUCTURE || curr->type==STRUCTURE_POINTER || curr->type==STRUCTURE_ARRAY || curr->type==STRUCTURE_POINTER_ARRAY;
	}
	return has;
}
