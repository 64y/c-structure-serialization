CC := gcc
LD := gcc


INCLUDE_DIR := include
SOURCE_DIR := src
OBJECT_DIR := obj
TARGET_DIR := bin
LIBRARY_DIR := lib


SOURCES := $(shell find $(SOURCE_DIR) -type f -name *.c ! -name "serializer.c")
OBJECTS := $(patsubst $(SOURCE_DIR)/%, $(OBJECT_DIR)/%, $(SOURCES:.c=.o))
-include $(OBJECTS:.o=.d)

CFLAGS := -Wall -g
LFLAGS := 
INC := -I $(INCLUDE_DIR)
INC_DEP := -I $(INCLUDE_DIR)

TARGET := generate_codecs


LIBRARY_SOURCE := $(SOURCE_DIR)/c_structure_serialization/serializer.c
LIBRARY_OBJECT := $(OBJECT_DIR)/c_structure_serialization/serializer.o

LIBRARY_CFLAGS := -Wall -fPIC
LIBRARY_LFLAGS := -ldl
LIBRARY_INC := -I $(INCLUDE_DIR)

LIBRARY := libcstructureserialization.a


build: clean directories library echo_compiling_objects $(TARGET)

clean:
	@$(RM) -rf $(OBJECT_DIR)
	@$(RM) -rf $(TARGET_DIR)
	@$(RM) -rf $(LIBRARY_DIR)

directories:
	@mkdir -p $(OBJECT_DIR)
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(LIBRARY_DIR)

library:
	@echo "Compiling library:"
	@mkdir -p $(dir $(LIBRARY_OBJECT))
	$(CC) $(LIBRARY_CFLAGS) $(LIBRARY_LFLAGS) $(LIBRARY_INC) -c -o $(LIBRARY_OBJECT) $(LIBRARY_SOURCE)
	ar -cvq $(LIBRARY_DIR)/$(LIBRARY) $(LIBRARY_OBJECT)
	
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

tests:
	gcc tests/main_primitives.c -o bin/tests -I tests -I $$C_STRUCTURE_SERIALIZATION_HOME/include -L $$C_STRUCTURE_SERIALIZATION_HOME -lcstructureserialization -ldl -lcrypto

.PHONY: clean directories build library echo_compiling_objects tests
