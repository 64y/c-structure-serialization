# C Structure Serialization

It is a library to serialize structure which contains: primitives, strings, structures or their multi dimentional types.

## Install and Uninstall

To install and uninstall **C Structure Serialization** methods `install` and `uninstall` from `install_and_uninstall.sh` file is used.

### Install
1. First of all get sources files:
```bash
git clone https://github.com/64y/c-structure-serialization
```
2. Then install **C Structure Serialization** by:
```bash
source install_and_uninstall.sh && install
```

Install is to build the source codes, copy nessesary files: `bin/generate_library`, `res`, `lib` into ~/.c_structure_serialization directory and to create environment variable **C_STRUCTURE_SERIALIZATION_HOME**. The build is deleted after all.

### Uninstall

To uninstall use the following:
```bash
source install_and_uninstall.sh && uninstall
```

## Makefile

Makefile contains several rules:

* `build` - to build program `generate_library` and compile library `libcstructureserialization.a`. Program and library have different source files;
* `library` - to compile library only;
* `clean` - remove `bin`, `lib`, `obj` directories;
* `example` - create example from `example/main.c`;
* `test` - create test  from `tests/main.c` for source code `*/utils` and `*/data_types`.

## Example
To run example program:

1. Edit `example/main.c`. Choose and uncomment examples you want to run:

```C
int main(int argc, char *argv[]) {
    // example_of_structure_with_primitives_members();
    // example_of_structure_with_string_member();
    // example_of_structure_with_array();
    // example_of_structure_with_matrix();
    // example_of_structure_with_matrices();
    // example_of_structure_with_matrices_of_strings();
    example_of_structure_with_structures_and_structures_pointers();
    // example_of_structure_with_matrices_of_structures();
    return 0;
}
```

2. Compile by calling the corresponding rule:
```bash
make example
```

3. Come to `bin` directory and call `./example`:
```bash
cd bin
./example
cd ../
```


## How To

There is a description how to use the library by yourself:

0. Lets say the structure of you project as follow:
```bash
my_project/
└ structures
    └ parrot.h
└ main.c
```

1. In you code `main.c`:

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

Create a serializer for structure by calling ```Serializer_create``` method, there you need to pass path to library file and structure's name.
```C
Serializer *parrot_serializer = Serializer_create("./my_lib", "Parrot");
```

Then call method `to_string` for instance `parrot` of structure `Parrot`:
```C
char *parrot_string = parrot_serializer->to_string(&parrot);
```

Output the string representaion of the instance `parrot` of your structure `Parrot`:
```C
puts(parrot_string);
```

Destroy serializer and free memory:
```C
Serializer_free(parrot_serializer);
free(parrot_string);
```

2. Create `./my_lib` library for files in `my_project/structures` directory:
```bash
> mkdir bin
> $C_STRUCTURE_SERIALIZATION_HOME/generate_library "my_project" "structures" "bin/my_lib"
```
You need to pass three arguments into `generate_library` program: path to project, path to structures in project's path, path to created library.

3. Compile program by:
```bash
> gcc my_program/main.c -o bin/main -I my_program -I $C_STRUCTURE_SERIALIZATION_HOME/include -L $C_STRUCTURE_SERIALIZATION_HOME -lcstructureserialization -ldl
```

4. Run program `./main`:
```bash
cd bin
./main
```

If you want to call `bin/main` you need to use "./bin/my_lib" library path in `main.c`.

## TODO
 - [ ] fix null in **json_codec**;
 - [ ] Implement **binary_codec**;
 - [ ] Work in dirs;
 - [ ] Write documentation.
