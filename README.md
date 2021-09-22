# C Structure Serialization

It is a library to serialize structure which contains: primitives, strings, structures or their multi dimentional types.

## Example

Example of running `main_primitives`:
1. Compile code:
```bash
make all
```
2. Compile library:
```bash
make library -f MakefileLib
```
3. Compile `main`:
```bash
cd tests
gcc main_primitives.c -o main -I structures/ -I ../include/ -L ../lib -lcstructureserialization -ldl -lcrypto -g
```
4. Generate files for structures in directory `structures` and compiling library:
``` bash
bash ../program.sh main structures
```
5. Run program:
```bash
./main
```

## TODO
 - [x] Implement **to_string** method.
 - [ ] Refactor current code to add more poly.
 - [ ] There is no json or bin codecs yet, only **to_string** method. So it is not a serialization for now.
 - [ ] There is a lot of memory leaks, so it only rush with `valgrind` support. (mb need to load all calling from library methods?)
 - [ ] Also it is possible to parse structure from binary itself, but I do not know how to do such a stuff.
 - [ ] Refactor model of program...
