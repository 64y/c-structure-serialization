# C Structure Serialization

It is a library to serialize structure which contains: primitives, strings, structures or their multi dimentional types.


## Run Examples

To run example:

1. Install `valgrind`, because `gcc` or `gdb` does not run complex examples:

```bash
sudo apt install gcc make valgrind 
```

2. Then compile program and run it:
```bash
make all

cd bin;valgrind ./program;cd ../
```


## Code Example

You can also use your own structure:

1. Add the header with your structure into the `include/structures` folder, and sources into the  the `src/structures`. Example of code:
```c
#ifndef PARROT_H
#define PARROT_H


typedef struct Parrot {
	char *name;
	int age;
} Parrot;

#endif
```

2. In your `main.c` you should import `c-structure-serialization` library headers:

```c
#include "serialization/registrate.h"
#include "serialization/serialize.h"
```

and your structure header file:
```c
#include "structures/parrot.h"
```
3. In main function:

3.1. Registrate structure by calling appropriate method:
```c
Serialize_registrate_structure("Parrot", "structures/parrot.h");
```

3.2. Initialize serialization structure with **to_string**, **json_encode**, **json_decode** methods, by compiling and loading shared library:
```c
Serialize *parrot_serialize = Serialize_create("Parrot");
```

3.3. Creating structure element:
```c
Parrot parrot = {"Tom", 5};
```

3.4. Getting string:
```c
char *parrot_string = parrot_serialize->to_string(&parrot);
puts(parrot_string);
```

3.5. Destroy serialization structure for parrot and free string memmory:
```c
Serialize_free(parrot_serialize);
free(parrot_string);
```

Other examples are in `include/examples/` folder.


## TODO
 - [x] Implement **to_string** method.
 - [ ] Refactor current code to add more poly.
 - [ ] There is no json or bin codecs yet, only **to_string** method. So it is not a serialization for now.
 - [ ] There is a lot of memory leaks, so it only rush with `valgrind` support. (mb need to load all calling from library methods?)
 - [ ] Also it is possible to parse structure from binary itself, but I do not know how to do such a stuff.
 - [ ] Refactor model of program...
