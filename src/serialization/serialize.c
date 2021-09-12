#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils/basic_defines.h"
#include "serialization/structure_info.h"
#include "serialization/serialize.h"


Serialize * Serialize_create(char *name) {
	compile_shared_library();
	StructureInfo *structureInfo = StructureInfo_create_by_name(name);
	if (access(PATH_SHARED_LIBRARY, F_OK) != 0) {
		error("open library. Structure does not registrated!");
	}
	Serialize *serialize = (Serialize *)malloc(sizeof(Serialize));
	serialize->handle = dlopen(PATH_SHARED_LIBRARY, RTLD_NOW|RTLD_GLOBAL);
	if (!serialize->handle) {
		error("dlopen library.");
	}
	*(void **) (&serialize->to_string) = dlsym(serialize->handle, structureInfo->to_string_name);
	if (dlerror()) {
		error("load \'to_string\' method in \'Serialize_create\'!");
	}
	*(void **) (&serialize->json_encode) = dlsym(serialize->handle, structureInfo->json_encode_name);
	if (dlerror()) {
		error("load \'json_encode\' method in \'Serialize_create\'!");
	}
	*(void **) (&serialize->json_decode) = dlsym(serialize->handle, structureInfo->json_decode_name);
	if (dlerror()) {
		error("load \'json_decode\' method in \'Serialize_create\'!");
	}
	StructureInfo_free(structureInfo);	
	return serialize;
}

void Serialize_free(Serialize *serialize) {
	if (serialize != NULL) {
		if (serialize->handle != NULL) {
			dlclose(serialize->handle);
			serialize->handle = NULL;
		}
		serialize->to_string = NULL;
		serialize->json_encode = NULL;
		serialize->json_decode = NULL;
		free(serialize);
		serialize = NULL;
	}
}
