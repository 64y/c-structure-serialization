#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/generate_source_codes/generate_attribute.h"
#include "c_structure_serialization/generate_source_codes/generate_pass_method.h"


char * generate_pass_method_declaration(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "void %s_pass(StructureUsageSet *structureUsageSet, StructureUsage *structureUsage);", structure->name);
		fclose(code_stream);
	}
	return code;
}

char * generate_pass_method_definition(Structure *structure) {
	char *code;
	{
		Tabs *tabs = Tabs_create();
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "%svoid %s_pass(StructureUsageSet *structureUsageSet, StructureUsage *structureUsage) {\n", Tabs_get(tabs), structure->name); Tabs_increment(tabs);
		fprintf(code_stream, "%sstructureUsage->status = USED;\n", Tabs_get(tabs));
		fprintf(code_stream, "%s%s *%s = (%s *) structureUsage->pointer;\n", Tabs_get(tabs), structure->name, structure->shortcut, structure->name);
		for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
			if (curr->type==STRUCTURE || curr->type==STRUCTURE_POINTER || curr->type==STRUCTURE_ARRAY || curr->type==STRUCTURE_POINTER_ARRAY) {
				char *attribute_pointer = generate_attribute_pointer(structure, curr);
				
				fprintf(
					code_stream,
					"%sif (%s%s!=NULL) {\n",
					Tabs_get(tabs),
					(string_equals(structure->name, curr->data_type)) ? "structureUsageSet->stage!=0 && ": "",
					attribute_pointer
				); Tabs_increment(tabs);
				
				char *code_add_pointer;
				{
					char *code_pointer;
					{
						char *attribute_data_type_upper = string_to_upper(curr->data_type);
						size_t code_pointer_length;
						FILE *code_pointer_stream = open_memstream(&code_pointer, &code_pointer_length);
						fprintf(code_pointer_stream, "StructureUsageSet_add(structureUsageSet, StructureUsage_create(%s, %s", attribute_data_type_upper, attribute_pointer);
						{
							free(attribute_data_type_upper);
							fclose(code_pointer_stream);
						}
					}
					size_t code_add_pointer_length;
					FILE *code_add_pointer_stream = open_memstream(&code_add_pointer, &code_add_pointer_length);
					if (curr->type==STRUCTURE_ARRAY || curr->type==STRUCTURE_POINTER_ARRAY) {
						char *code_loop_format = generate_attribute_with_loop(structure, curr, tabs, false);
						char *code_loop;
						{
							size_t code_loop_length;
							FILE *code_loop_stream = open_memstream(&code_loop, &code_loop_length);
							fprintf(code_loop_stream, code_loop_format, "", code_pointer, "));");
							{
								fclose(code_loop_stream);
							}
						}
						fprintf(code_add_pointer_stream, "%s", code_loop);
						{
							free(code_loop_format);
							free(code_loop);
						}
					} else {
						fprintf(code_add_pointer_stream, "%s%s%s", Tabs_get(tabs), code_pointer, "));\n");
					}
					{
						free(code_pointer);
						fclose(code_add_pointer_stream);
					}
				}
				
				fprintf(code_stream, "%s", code_add_pointer); Tabs_decrement(tabs);
				fprintf(code_stream, "%s}\n", Tabs_get(tabs));
				{
					free(attribute_pointer);
					free(code_add_pointer);
				}
			}
		}
		Tabs_decrement(tabs);
		fprintf(code_stream, "%s}", Tabs_get(tabs));
		{
			Tabs_free(tabs);
			fclose(code_stream);
		}
	}
	return code;
}

