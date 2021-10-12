# Examples

- [Example Method](#example-method)
- [Example of Structure With Primitives](#example-of-structure-with-primitives)
- [Example of Structure with String Member](#example-of-structure-with-string-member)
- [Example of Structure with Array](#example-of-structure-with-array)
- [Example of Structure with Matrix](#example-of-structure-with-matrix)
- [Example of Structure with Matrices](#example-of-structure-with-matrices)
- [Example of Structure with Matrices of Strings](#example-of-structure-with-matrices-of-strings)
- [Example of Structure with Structures and Structures Pointers](#example-of-structure-with-structures-and-structures-pointers)
- [Example of Structures with Matrixes of Structures](#example-of-structures-with-matrixes-of-structures)


## Example Method

```C
void example (
	char *example_name,
	char *library_path,
	char *structure_name,
	void * (*structure_generate) (void),
	void (*structure_free) (void *structure),
	int DO_FLAG
) {
	printf(" = = = Example of %s = = = \n\n", example_name);
	
	Serializer *serializer = Serializer_create(library_path, structure_name);
	
	void *structure = structure_generate();
	
	if (DO_FLAG & DO_TO_STRING) {
		char *structure_string = serializer->to_string(structure);
		printf("TO_STRING:\n%s\n\n", structure_string);
		{
			free(structure_string);
		}
	}
	if (DO_FLAG & DO_JSON_ENCODE) {
		char *structure_json = serializer->json_encode(structure);
		printf("JSON_ENCODE:\n%s\n\n", structure_json);
		{
			free(structure_json);
		}
	}
	if (DO_FLAG & DO_JSON_DECODE) {
		char *structure_json = serializer->json_encode(structure);
		void *structure_temp = serializer->json_decode(structure_json);
		char *structure_temp_string = serializer->to_string(structure_temp);
		printf("JSON_DECODE:\n%s\n\n", structure_temp_string);
		{
			free(structure_json);
			structure_free(structure_temp);
			free(structure_temp_string);
		}
	}
	if (DO_FLAG & DO_BYTE_ENCODE) {
		Data *structure_data = serializer->byte_encode(structure);
		char *structure_data_string = Data_to_string(structure_data);
		printf("BYTES_ENCODE:\n%s\n\n", structure_data_string);
		{
			Data_free(structure_data);
			free(structure_data_string);
		}
	}
	if (DO_FLAG & DO_BYTE_ENCODE) {
		Data *structure_data = serializer->byte_encode(structure);
		void *structure_temp = serializer->byte_decode(structure_data);
		char *structure_temp_string = serializer->to_string(structure_temp);
		printf("BYTES_DECODE:\n%s\n\n", structure_temp_string);
		{
			Data_free(structure_data);
			structure_free(structure_temp);
			free(structure_temp_string);
		}
	}
	{
		structure_free(structure);
		Serializer_free(serializer);
	}
	printf(" = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n\n");
}
```
* [Source Code](example/examples/example_template.h);


## Example of Structure With Primitives
```C
typedef struct AllPrimitives {
	char c;
	unsigned char uc;
	byte b;
	short s;
	int i;
	long l;
	float f;
	double d;
} AllPrimitives;
```
* [Structure](example/structures/all_primitives.h);
* [Example](example/examples/0_primitives.h);
* [Example Output](EXAMPLES_OUTPUT.md#example-output-of-structure-with-primitives-members).

## Example of Structure with String Member
```C
typedef struct Parrot {
	char *name;
	int age;
} Parrot;
```
* [Structure](example/structures/parrot.h);
* [Example](example/examples/1_string.h);
* [Example Output](EXAMPLES_OUTPUT.md#example-output-of-structure-with-string-member).


## Example of Structure with Array
```C
typedef struct Array {
	int arr_n;
	int *arr;
} Array;
```
* [Structure](example/structures/array.h);
* [Example](example/examples/2_array.h);
* [Example Output](EXAMPLES_OUTPUT.md#example-output-of-structure-with-array).


## Example of Structure with Matrix
```C
typedef struct Matrix3D {
	int matrix_o;
	int matrix_n;
	int matrix_m;
	int ***matrix;
} Matrix3D;
```
* [Structure](example/structures/matrix3d.h);
* [Example](example/examples/3_matrices.h);
* [Example Output](EXAMPLES_OUTPUT.md#example-output-of-structure-with-matrix).


## Example of Structure with Matrices
```C
typedef struct Arrays {

	int arr_a;
	int arr_b;
	int **arr;
	
	int brr[2][3][4][5];
	
	int crr_0;
	int crr_1;
	int crr_2;
	int crr[10][10][10];
	
	int drr_2;
	int drr_3;
	int drr_4;
	int*** drr[2][3];
	
	int err_0;
	int err_1;
	int err_2;
	int err_3;
	int ** err[5][5];
} Arrays;
```
* [Structure](example/structures/arrays.h);
* [Example](example/examples/3_matrices.h);
* [Example Output](EXAMPLES_OUTPUT.md#example-output-of-structure-with-matrices).


## Example of Structure with Matrices of Strings
```C
typedef struct Strings {
	
	int stra_0;
	int stra_1;
	char ***stra;
	
	char strb[5][5][32];
	
	int strc_0;
	int strc_1;
	char strc[4][4][10];
	
	int strd_2;
	int strd_3;
	char*** strd[6][6];
	
	int stre_0;
	int stre_1;
	int stre_2;
	int stre_3;
	char***stre[7][7];
} Strings;
```
* [Structure](example/structures/strings.h);
* [Example](example/examples/3_matrices.h);
* [Example Output](EXAMPLES_OUTPUT.md#example-output-of-structure-with-matrices-of-strings).


## Example of Structure with Structures and Structures Pointers
```C
typedef struct Cat {
	int age;
	char *name;
	double cute;
	struct Cat *next;
} Cat;

typedef struct Dog {
	int age;
	char *name;
	char *color;
	struct Dog *next;
} Dog;

typedef struct PetsSizes {
	int total;
	int cats;
	int dogs;
} PetsSizes;


typedef struct Pets {
	PetsSizes size;
	Cat *head_cats;
	Dog *head_dogs;
} Pets;
```
* [Structure](example/structures/pets.h);
* [Example](example/examples/4_structures.h);
* [Example Output](EXAMPLES_OUTPUT.md#example-output-of-structure-with-structures-and-structures-pointers).


## Example of Structures with Matrixes of Structures
```C
typedef struct Point {
	int x;
	int y;
} Point;

typedef struct Circle {
	Point c;
	int r;
} Circle;

typedef struct Rectangle {
	Point a;
	Point b;
} Rectangle;

typedef struct Triangle {
	Point a;
	Point b;
	Point c;
} Triangle;

typedef struct Figures {
	
	int circles_0;
	int circles_1;
	Circle ***circles;
	
	Triangle triangles[5][5];
	
	int rectangles_a;
	int rectangles_b;
	int rectangles_c;
	int rectangles_d;
	int rectangles_e;
	Rectangle*** rectangles[10][10][10];
} Figures;
```
* [Structure](example/structures/figures.h);
* [Example](example/examples/5_matrices_of_structures.h);
* [Example Output](EXAMPLE_OUTPUT.md#example-output-of-structure-with-matrices-of-structures).
Example Output of Structure with Matrices of Structures