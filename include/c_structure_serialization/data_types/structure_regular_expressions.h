/** @file
@brief The declaration of RegularExpression and StructureRegularExpressions structures and their methods. */
#ifndef STRUCTURES_REGULAR_EXPRESSIONS_H
#define STRUCTURES_REGULAR_EXPRESSIONS_H


#include <stdbool.h>
#include <stddef.h>
#include <regex.h>


/** @brief Regular Expression structure.
@details RegularExpression is described by its pattern, number of matches in pattern and pointer for an instance of structure regex_t. */
typedef struct RegularExpression {
	char *pattern; ///< The pattern.
	size_t num_matches; ///< Number of matches in pattern.
	regex_t *re; ///< A pointer for an instance of structure regex_t.
} RegularExpression;


/** @brief Creates RegularExpression.
@details Method creates an instance of structure RegularExpression.
@param pattern string pattern in REG_EXTENDED format;
@param num_matches number of matches substring in parsing by pattern string.
@return Created RegularExpression. */
RegularExpression * RegularExpression_create(char *pattern, size_t num_matches);

/** @brief Frees memory of RegularExpression.
@details Methods frees string pattern, frees variable re and frees the allacated memory for an instance of structure RegularExpression and assigns a NULL value.
@param regularExpression A pointer to instance of structure RegularExpression.*/
void RegularExpression_free(RegularExpression *regularExpression);

/** @brief Gets string of RegularExpression.
@details Method creates a string representation for an instance of structure RegularExpression.
@param regularExpression A pointer to instance of structure RegularExpression.
@return A string representation of RegularExpression. */
char * RegularExpression_to_string(RegularExpression *regularExpression);


/** @brief Checks string for matching the pattern in RegularExpression.
@details Method checks the matcheness of string to the pattern in an instance of structure RegularExpression.
@param regularExpression A pointer to instance of structure RegularExpression.
@param string A string to find matches in.
@return Returns True if string match pattern or return False otherwise. */
bool RegularExpression_match(RegularExpression *regularExpression, char *string);

/** @brief Creats an array of matches for string by pattern.
@details Method creates an array of matches by pattern for string.
@param A pointer to instance of structure RegularExpression;
@param string A string to find matches in.
@return  Array of matches.*/
char ** RegularExpression_parse(RegularExpression *regularExpression, char *string);


/** @brief Regular Expressions for Structure.
@details Regular expressions for Structure: start of structure, attributes, end of structure. */
typedef struct StructureRegularExpressions {
	RegularExpression *structureStart; ///< Regular expression for the start of structure (typedef struct Name {).
	RegularExpression *attribute; ///< Regular expression for attributes: primitives, string, structures and arrays (\tName **name[][][]).
	RegularExpression *structureEnd; ///< Regular expression for the end of structure (} Name;).
} StructureRegularExpressions;

/// A global variable structureRegularExpressions
extern StructureRegularExpressions *structureRegularExpressions;

/** @brief Creates a global variable structureRegularExpressions.
@details */
void StructureRegularExpressions_init();

/** @brief Frees memory of variable structureRegularExpressions.
@details */
void StructureRegularExpressions_fini();

#endif
