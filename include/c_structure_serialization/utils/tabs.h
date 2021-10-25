/** @file
@brief The declaration of Tabs structure and its methods. */
#ifndef TABS_H
#define TABS_H


#include <stddef.h>


/** @brief Tabs structure determine the tabs on each line of code.
@details Tabs structure controls the length of tabs in current line. Its tabs length increases when braces are opening, and decreases otherwise. It used in the beginning of the string to determine current tab position. */
typedef struct Tabs {
	size_t tab_length; ///< The length of tab string.
	char *tab; ///< The symbol of tabs, '\t' - is by default.
	size_t string_length; ///< The length of string of tabs.
	size_t string_length_max; ///<  The max length of string, default is 32*tab_length.
	char *string; ///< The string of tabs.
} Tabs;

/** @brief Creates Tabs.
@details Method creates an instance of structure Tab with default tab symbol - '\t' and max length of string - 32 chars.
@return Created Tabs. */
Tabs * Tabs_create();

/** @brief Creates Tabs with specific tab.
@details Method creates an instance of structure Tab with tab symbol - tab and max length of string - 32*strlen(tab) chars.
@param tab The tab symbol.
@return Created Tabs. */
Tabs * Tabs_create_by_tab(char *tab);

/** @brief Frees memory of Tabs.
@details Method frees allocated memory for tab and string and assigns a NULL value, the sizes is assignes to zero and frees the memory for the instance of the structure Tabs and assigns a NULL value.
@param tabs The pointer to the instance of structure Tabs. */
void Tabs_free(Tabs *tabs);

/** @brief Gets string of Tabs.
@details Method creates a string representation for an instance of structure Array
@param tabs The pointer to the instance of structure Tabs.
@return String representation of Tabs. */
char * Tabs_to_string(Tabs *tabs);


/** @brief Gets Tabs symbol.
@details Method returns the tab symbol.
@param tabs The pointer to the instance of structure Tabs.
@return Tab symbol. */
char * Tabs_get_tab(Tabs *tabs);

/** @brief Gets Tabs string.
@details 
@param tabs The pointer to the instance of structure Tabs.
@return Current tabs string. */
char * Tabs_get(Tabs *tabs);

/** @brief Increments Tabs.
@details 
@param tabs The pointer to the instance of structure Tabs. */
void Tabs_increment(Tabs *tabs);

/** @brief Decrements Tabs.
@details 
@param tabs The pointer to the instance of structure Tabs. */
void Tabs_decrement(Tabs *tabs);

#endif
