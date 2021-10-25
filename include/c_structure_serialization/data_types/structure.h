/** @file
@brief The declaration of Structure structure and its methods. */
#ifndef STRUCTURE_H
#define STRUCTURE_H


#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#include "c_structure_serialization/utils/array.h"
#include "c_structure_serialization/data_types/attribute.h"


/** @brief Structure is a single linked list of Attributes. */
typedef struct Structure {
	char *file_path; ///< The file path of structure.
	char *name; ///< The name of structure.
	char *name_lower; ///< Lower case name.
	char *name_upper; ///< Upper case name.
	char *shortcut; ///< Shortcut of structure name.
	size_t size; ///< Number of Attributes in Strcuture.
	Attribute *head; ///< First element in Structure.
} Structure;


/** @brief Creates Structure by its path to file and structure name.
@details Method creates an instance of structure Structure.
@param file_pate The path to file;
@param name The name of Structure;
@return Created Structure. */
Structure * Structure_create_by_file_path_and_name(char *file_path, char *name);

/** @brief Creates Structure by its path to file and array of source code lines.
@details Method creates an instace of structure Structure by parsing lines of codes into Attributes.
@param file_path The path to file;
@param source_code An array of source code lines.
@return Created Structure. */
Structure * Structure_create_by_file_path_and_source_code(char *file_path, Array *source_code);

/** @brief Frees memory of Structure.
@details Methods frees string file_path, name, name_lower name_upper; assigns a zero value to size, frees alloacted memory for each Attribute in Structure by calling a Attribtue_free method and frees an instance of structure Structure.
@param structure A pointer to instance of structure Structure.*/
void Structure_free(Structure *structure);

/** @brief Gets string of Structure.
@details Method creates a string representation for an instance of structure Structure.
@param structure A pointer to instance of structure Structure.
@return A string representation of Structure. */
char * Structure_to_string(Structure *structure);


/** @brief Adds Attribute into Structure.
@details Method adds Attribute as a head if Structure is empty, and method adds Attribute into the end of list of structures otherwise.
@param structure A pointer to instance of structure Structure, a source list;
@param attribute A pointer to instance of structure Attribute, an element to be added. */
void Structure_add(Structure *structure, Attribute *attribute);

/** @brief Delete Attribute from Structure.
@details Method delete Attribute from list of attributes in Structure.
@param structure A pointer to instance of structure Structure, a source list;
@param attribute A pointer to instance of structure Attribute, an element to be deleted.
@return If attribute was deleted returns True, otherwise returns False. */
bool Structure_delete(Structure *structure, Attribute *attribute);

/** @brief Checks Structure for strings.
@details If any of attribute in Structure is a string or an array of strings, then method returns True. Method returns False otherwise.
@param structure A pointer to instance of structure Structure.
@return If structure contains string attribute return True, and False otherwise. */
bool Structure_contains_string_attributes(Structure *structure);

/** @brief Check Structure for arrays.
@details If any of attribute in Structure is an array of primitives, strings or structures, then method returns True. Method returns False otherwise.
@param structure A pointer to instance of structure Structure.
@return If structure contains array attribute return True, and False otherwise. */
bool Structure_contains_array_attributes(Structure *structure);

/** @brief Check Structure for structures.
@details If any of attribute in Structure is a structure or an array of structure, then method returns True. Method returns False otherwise.
@param structure A pointer to instance of structure Structure.
@return If structure contains structure attribute return True, and False otherwise. */
bool Structure_contains_structure_attributes(Structure *structure);


/** @brief Array's create method for Structure. */
void * array_Structure_create(va_list structure_arguments);
/** @brief Array's free method for Structure. */
void array_Structure_free(void *structure);
/** @brief Array's to_string method for Structure. */
char * array_Structure_to_string(void *structure);
/** @brief Creates Array for instance of structure Structure. */
Array * Array_create_for_Structure();

#endif
