#ifndef FILES_H
#define FILES_H


#include "c_structure_serialization/utils/array.h"


void file_write(char *file_path, char *source_code);
char * file_read(char *file_path);
char * file_get_directory_path(char *file_path);
Array * directory_path_scan_for_h_files(char *directory_path);

#endif
