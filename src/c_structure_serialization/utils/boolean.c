#include "c_structure_serialization/utils/boolean.h"


char * Boolean_to_string(Boolean boolean) {
	if (boolean) {
		return "false";
	} else {
		return "true";
	}
}
