/** @file
@brief Utils methods to work with files and directories. */
#ifndef FILES_H
#define FILES_H


#include "c_structure_serialization/utils/array.h"


/** @brief Writes into file.
@details Method writes source_code into the file with path file_path.
@param file_path A path to file;
@param source_code A source code. */
void file_write(char *file_path, char *source_code);

/** @brief Reads from file.
@details Method reads and concatenates lines from file with path file_path.
@param file A path to file.
@return Concatenated lines.*/
char * file_read(char *file_path);


/** @brief Gets an Array of *.h files in directory with path direcoty_path and each of its subdirectory.
@details Method scans directory with path directory path and all its subdirectories for *.h files and put them into Array.
@param directory_path
@return Array of header files. */
Array * directory_path_scan_for_h_files(char *directory_path);

#endif
