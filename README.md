# C Structure Serialization

It is a library to serialize structure which contains: primitives, strings, structures or their multi dimentional types.

## TODO
 - [x] Implement **to_string** method.
 - [ ] Refactor current code to add more poly.
 - [ ] There is no json or bin codecs yet, only **to_string** method. So it is not a serialization for now.
 - [ ] There is a lot of memory leaks, so it only rush with `valgrind` support. (mb need to load all calling from library methods?)
 - [ ] Also it is possible to parse structure from binary itself, but I do not know how to do such a stuff.
 - [ ] Refactor model of program...
