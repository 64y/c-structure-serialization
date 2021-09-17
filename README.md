# C Structure Serialization

It is contains from two parts:
1. User static library from `serialize` folder in you code.
2. Run `program.sh` from `generate_codecs` to generate code and create shared library.

## TODO
 - [x] Implement **to_string** method.
 - [ ] Refactor current code to add more poly.
 - [ ] There is no json or bin codecs yet, only **to_string** method. So it is not a serialization for now.
 - [ ] There is a lot of memory leaks, so it only rush with `valgrind` support. (mb need to load all calling from library methods?)
 - [ ] Also it is possible to parse structure from binary itself, but I do not know how to do such a stuff.
 - [ ] Refactor model of program...
