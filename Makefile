CC := gcc
LD := gcc

INCLUDE_DIR := include
SOURCE_DIR := src
OBJECT_DIR := obj
TARGET_DIR := bin
LIBRARY_DIR := lib
SOURCES := $(shell find $(SOURCE_DIR) -type f -name *.c ! -name "serializer.c" ! -name "data.c")
OBJECTS := $(patsubst $(SOURCE_DIR)/%, $(OBJECT_DIR)/%, $(SOURCES:.c=.o))
-include $(OBJECTS:.o=.d)
CFLAGS := -Wall -g
LFLAGS := 
INC := -I $(INCLUDE_DIR)
INC_DEP := -I $(INCLUDE_DIR)
TARGET := generate_library

LIBRARY_SOURCES := $(shell find $(SOURCE_DIR) -type f -name "serializer.c" -o -name "data.c")
LIBRARY_OBJECTS := $(patsubst $(SOURCE_DIR)/%, $(OBJECT_DIR)/%, $(LIBRARY_SOURCES:.c=.o))
LIBRARY_CFLAGS := -Wall -fPIC
LIBRARY_LFLAGS := -ldl
LIBRARY_INC := -I $(INCLUDE_DIR)
LIBRARY := libcstructureserialization.a

EXAMPLE_DIR := example
EXAMPLE_TARGET := example
EXAMPLE_LIBRARY_NAME := my_lib

TESTS_DIR := tests
TESTS_TARGET := test

build: clean directories library echo_compiling_objects $(TARGET)

clean:
	@$(RM) -rf $(OBJECT_DIR)
	@$(RM) -rf $(TARGET_DIR)
	@$(RM) -rf $(LIBRARY_DIR)

directories:
	@mkdir -p $(OBJECT_DIR)
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(LIBRARY_DIR)

library: $(LIBRARY_OBJECTS)
	@echo "Compiling library:"
	ar -cvq $(LIBRARY_DIR)/$(LIBRARY) $^
	
$(TARGET): $(OBJECTS)
	@echo "\nCompiling target:"
	$(CC) -o $(TARGET_DIR)/$(TARGET) $^ $(LFLAGS)

echo_compiling_objects:
	@echo "\nCompiling objects:"

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INC_DEP) -MM $(SOURCE_DIR)/$*.c > $(OBJECT_DIR)/$*.d
	@cp -f $(OBJECT_DIR)/$*.d $(OBJECT_DIR)/$*.d.tmp
	@sed -e 's|.*:|$(OBJECT_DIR)/$*.o:|' < $(OBJECT_DIR)/$*.d.tmp > $(OBJECT_DIR)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(OBJECT_DIR)/$*.d.tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(OBJECT_DIR)/$*.d
	@rm -f $(OBJECT_DIR)/$*.d.tmp

example:
	@mkdir -p $(TARGET_DIR)
	@$$C_STRUCTURE_SERIALIZATION_HOME/generate_library $(EXAMPLE_DIR) "structures" $(TARGET_DIR)/$(EXAMPLE_LIBRARY_NAME)
	@$(CC) $(shell find $(EXAMPLE_DIR) -type f -name "*.c") -o $(TARGET_DIR)/$(EXAMPLE_TARGET) -I $(EXAMPLE_DIR) -I $$C_STRUCTURE_SERIALIZATION_HOME/include -L $$C_STRUCTURE_SERIALIZATION_HOME -lcstructureserialization -ldl

test:
	@mkdir -p $(TARGET_DIR)
	@$(CC) -o $(TARGET_DIR)/$(TESTS_TARGET) -I $(INCLUDE_DIR) $(LFLAGS) $(shell find $(SOURCE_DIR) -type f -name "*.c" ! -name "main.c" ! -name "serializer.c") $(TESTS_DIR)/main.c 

.PHONY: clean directories build library echo_compiling_objects example test
