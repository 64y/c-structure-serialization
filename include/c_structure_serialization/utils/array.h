/** @file
@brief The declaration of Array structure and methods to work with it. */
#ifndef ARRAY_H
#define ARRAY_H


#include <stdarg.h>
#include <stddef.h>


/** @brief Generic array.
@details Array structure is a generic array for one data type only. Methods to create, free and receive a string representation of element should be specified to work with array for appropriate type.
*/
typedef struct Array {
	size_t size; ///< Size of pointers array.
	void **elements; ///< An array of pointers to elements of abstract type.
	void * (*element_create) (va_list element_arguments); ///< A pointer to create element method.
	void (*element_free) (void *element); ///< A pointer to to_string element method.
	char * (*element_to_string) (void *element); ///< A pointer to free element method.
} Array;

/** @brief Creates Array.
@details Method creates an instance of structure Array, by specifying methods create, free and to_string for appropriate data type.
@param element_create A pointer to create element method;
@param element_free A pointer to free element method;
@param element_to_string A pointer to to_string element method.
@return Created element of structure Array.*/
Array * Array_create(void * (*element_create) (va_list element_arguments), void (*element_free) (void *element), char * (*element_to_string) (void *element));

/** @brief Frees memory of Array.
@details Method frees the allocated memory for an instance of structure Array: size is assigned to zero; for each element in array of pointers elements the element_free method is used, frees arrays of pointers elements and assigned a NULL value; element_create, element_free and element_to_string are asign NULL value; frees an instance of structure Array array and asigns a NULL value.
@param array A pointer to an instance of structure Array.
*/
void Array_free(Array *array);

/** @brief Gets string of Array.
@details Method creates a string representation for an instance of structure Array.
@param array A pointer to an instance of structure Array.
@return A string representatio of Array.*/
char * Array_to_string(Array *array);


/** @brief Creates a new element and appends it to Array.
@details Methods creates a new instance of element by using element_create method with ... arguments and appends this element to array of pointers elements.
@param array A pointer to an instance of structure Array;
@param ... A list of arguments for method element_create. */
void Array_add(Array *array, ...);

/** @brief Adds element to Array.
@details Methods appends an instance of element to array of pointers elements.
@param array A pointer to an instance of structure Array;
@param element A new element of array. */
void Array_put(Array *array, void *element);

/** @brief Gets element of Array by index.
@details Methods returns a pointer to element in array of pointers elements.
@param array A pointer to an instance of structure Array;
@param index An index of element in array of pointers elements.
@return Element of array of pointers elements with specific index. */
void * Array_get(Array *array, int index);

/** @brief Gets size of Array.
@details Methods returns a size of pointers of elements array elements.
@param array A pointer to an instance of structure Array.
@return Value size - the size of array. */
size_t Array_size(Array *array);

/** @brief Sorts Array.
@details Methods sorts an array of pointers to elements by using a cmp comparator.
@param array A pointer to an element of structure Array;
@param cmp A method to compare elements of array of pointer to elements. */
void Array_sort(Array *array, int (*cmp) (const void *a, const void *b));

#endif
