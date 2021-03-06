# C Structure Serialization
It can be used to get the string representation of structure and serialize/deserialize structure with json or byte format. Also you can add your own codecs.

## Proposed Solution
The only true solution is to implement your own codecs by yourself for each structure you need according to your tasks. Also you have to edit your codec each time your structure is edited. But it is boring and annoying to write the almost same code for each structure separately. It is very common and cycled process, that's why it should be automated.

You can `fwrite`/`fread` whole structure if each of its structure member is allocated in static declarations. For example you want to collect a matrix of Points (x, y coordinated) in structure, and this matrix can be 5x5, 100x100 or even 10^5x10^5. Then you are able to serialize it only if matrix is staticly allocated for size 10^5x10^5. And each time you want to serialize/deserialize matrix of Points, it would be performed for its max dimensions, which is a wastage of memory and bandwich.

In theory you are able to extract information about any structure during program execution, with `type Structure` in `gdb` or parsing DWARF in `objdump` but when program was compiled with `-g` flag only.

Proposed solution consits of two parts:
1. Program to generate sources and create a library of methods for each structure in specified folder;
2. Compiled library to use apropriate methods from generated one based on structure name.

All you need is Linux/shell/bash/make/gcc.

## Example
There is an example of creating library for structure and using this library by `Serializer` to get the output from `to_string` method.

0. Lets say the structure of project is looks as follow:
```bash
src/
└ structures
    └ parrot.h
  └ main.c
```

1. In `main.c`:
```C
#include <stdio.h>
#include <stdlib.h>

#include "pets/parrot.h"
#include <c_structure_serialization/serializer.h>


int main(int argc, char *argv[]) {
	Parrot parrot = {"Tom", 5};
	
	Serializer *parrot_serializer = Serializer_create("./parrot_library", "Parrot");
	char *parrot_string = parrot_serializer->to_string(&parrot);
	puts(parrot_string);
	{
		Serializer_free(parrot_serializer);
		free(parrot_string);
	}
	return 0;
}
```

Include the header file of structure you want to use:
```C
#include "structures/parrot.h"
```

Include the  **C Structure Serialization** serializer:
```C
#include <c_structure_serialization/serializer.h>
```

Create an instance of structure:
```C
Parrot parrot = {"Tom", 5};
```

Create a serializer for structure by calling `Serializer_create` method, there you need to pass path to library file and structure name.
```C
Serializer *parrot_serializer = Serializer_create("./parrot_library", "Parrot");
```

Then call method `to_string` for `parrot`:
```C
char *parrot_string = parrot_serializer->to_string(&parrot);
```

Output the `parrot`'s string:
```C
puts(parrot_string);
```

Destroy serializer and free memory:
```C
Serializer_free(parrot_serializer);
free(parrot_string);
```

2. Create `./parrot_library` library for files in `project/structures` directory:
```bash
> mkdir bin
> $C_STRUCTURE_SERIALIZATION_HOME/generate_source_codes_and_library path_to_project=src path_to_library=bin/parrot_library
```

You need to pass three arguments into `generate_library` program: path to project, path to structures in project's path, path to created library.

3. Compile program by:
```bash
> gcc src/main.c -o bin/main -I src -I $C_STRUCTURE_SERIALIZATION_HOME/include -L $C_STRUCTURE_SERIALIZATION_HOME -lcstructureserialization -ldl
```

4. Run program `./main`:
```bash
cd bin;./main;cd ../;
```

If you want to call `bin/main` you need to use "./bin/parrot_library" library path in `main.c`.

There are several examples for different structures - [EXAMPLES](EXAMPLES.md).
```bash
make example;cd bin;./example;cd ../;
```

## Project

### Short Description of Files
```
c_structure_serialization - directory of main program;
 utils - contains helpful structures and methods;
  data.h data.c - `Data` structure is byte array and its size;
  array.h array.c - `Array` structure is an abstract array;
  string.h string.c - utilities to work with strings;
  files.h files.c - utilities to work with files;
  program_arguments.h program_arguments.c - `ProgramArguments` structure is a parsed program args;
  tabs.h tabs.c - `Tabs` structure helps to control tabs in the begining of each line of created source codes;
 data_types - contains structures to parse source code and create a representaion of each structure in program;
  attribute_type.h attribute_type.c - `AttributeType` enum;
  basic_type.h basic_type.c - `BasicType` structure to describe primitive types;
  dimension.h dimension.c - `Dimension` structure contains dimension sizes and variables of array in structure;
  attribute.h attribute.c - `Attribute` structure represents attribute of structure;
  structure.h structure.c - `Structure` structure parse lines of source codes to extract attributes;
  structure_regular_expressions.h structure_regular_expressions.c - `RegularExpression` structure, `StructureRegularExpressions` - regex for structure;
 generate_source_codes - directory of methods to generate source code for future library;
 	generate_sources.h generate_sources.c - contains method to parse files for structures use ProgramArgument to generate source codes and compile dynamic shared library file;
  generate_library.h generate_library.c - contains method to generate source codes for each structure in dynamic library;
  generate_code_for_to_string.h generate_code_for_to_string.c - methods to generate `to_string` method source code;
  generate_code_for_json_codec.h generate_code_for_json_codec.c - methods to generate json codec source code;
  generate_code_for_byte_codec.h generate_code_for_byte_codec.c - methods to generate byte codec source code;
 serializer.h serializer.c - `Serializer` structure created based on library file and structure names;
main.c - main for `generate_source_codes_and_library` program - Target to build.

res/src - directory of sources to used in creating library;
 _structure
  pointer.h pointer.c - `Pointer` structure;
  pointer_set.h pointer_set.c - `PointerSet` structure;
  structure_info.h structure_info.c - `StructureName` enum and `StructureMethods` enum;
  codec.h codec.c - `methods` matrix and basic codecs methods;
 _utils
  data.h data.c - `Data` structure - duplicate;
  base64.h base64.c - methods to use base64 algorithm for bytes and strings;
  write_read_uint32.h write_read_uint32.c - method to write/read uint32 (30 bit value, 2 bit size) value;
includes.h - header for all sources.

example
 examples - directory of examples for structures;
 structures - directory of structures headers;
 main.c - main for `example program`.

install_and_uninstall.sh - a install/uninstall script.

Makefile - a makefile.

documentation.doxygen - a config file to generate doxygen documentation.

README.md - this readme file;
EXAMPLES.md - files of examples for different structure;
EXAMPLES_OUTPUT.md - files of examples output.
```

### Makefile
Makefile contains several rules:
- `build` - to build program `generate_library` and compile library `libcstructureserialization.a`. Program and library have different source files;
- `clean` - remove `bin`, `lib`, `obj` directories;
- `example` - create example from `example/main.c`;
- `library` - to compile library only;
- `test` - create test  from `tests/main.c` for source code `*/utils` and `*/data_types`.

### Install and Uninstall
To install and uninstall **C Structure Serialization** methods `install` and `uninstall` from [`install_and_uninstall.sh`](install_and_uninstall.sh) file can be used.

#### Install
1. First of all get sources files:
```bash
git clone https://github.com/64y/c-structure-serialization
```
2. Then install **C Structure Serialization**:
```bash
source install_and_uninstall.sh && install
```

Installation:
- builds the project with ```make build``` rule from [`Makefile`](Makefile);
- creates directory `~/.c_structure_serialization`;
- adds environment variable **C_STRUCTURE_SERIALIZATION_HOME=** `~/.c_structure_serialization` by adding aproppriate line into `~/.bashrc` file and executing `source ~/.bashrc`;
- copies files into project home directory:
	- `bin/generate_source_codes_and_library` file;
	- `lib/libcstructureserialization.a` file;
	- `res` dictionary;
	- `serializer.h` and `data.h` files into `include` folder with saved paths.
- cleans the project with ```make clean``` rule.

#### Uninstall
To uninstall:
```bash
source install_and_uninstall.sh && uninstall
```

Uninstallation:
- removes project home directory with all files;
- removes project home directory exporting line from `~/.bashrc` and `source ~/.bashrc`.

### Structure Definition Limits
There are several requirements for structure definition:
- allowed letters in names: 0-9, a-z, A-Z, '_';
- structure name should starts with capital letter, because of `shortcut` in `Structure` structure;
- structure should be `typedef`ed;
```C
typedef struct Cat {
    ...
} Cat;
```
- one member per line in structure;
- only variables in structure (no pointer to methods and etc);
- allowed primitives: `char`, `unsigned char`, `byte`, `short`, `int`, `unsigned`, `long`, `float`, `double`, - you can also add primitives you need by editing `basic_type.c`;
- array:
	- static:
```C
type arr[5][5][5]; 
```
	- dynamic, there sizes should be defined and each dimension name start with array name:
```C
int arr_n;
int arr_m;
int arr_l;
int ***arr;
```
	- combined:
```C 
int arr_3;
int arr_4;
int arr_5;
int ***arr[5][10];
int brr_1;
int brr_2;
int *brr[2];
```
- string:
```C
char *str;
```
- string array:
```C
char stra[5][5]; // NOT string array - matrix of char
int strb_2;
char strb[5][5];
char *strc[5];
int strd_2;
char **strd[5];
int stre_1;
int stre_2;
char **stre[5];
```
- structure, structure pointer and matrices from them.

## Future Improvements
* Add Smart walk though pointer in codec: exclude if attribute->datatype==structure->datatype);
* Find another way to get structure details. It should be more beautiful and effective;
* Rework code to generalize it structure;
* Json Codec add extra braces and tabs;
* Byte Codec add compression;
* Write test for all functionallity;
* Write more comples examples;
* Write another codecs;
* Develop Object structure in C.

## My C Preferences
You might find 'em in source codes:
- camel case for names and underscore for functions;
- method should return single instance of data instead of pointers in arguments;
- I am fond of `alloc` and `free` memory;
- highlighting `fclose` and `free` with braces;
- `typedef`ing structures to avoid using `struct`;
- it is good to have `create`, `free` and `to_string` methods for every structure.
