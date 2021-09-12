CC := gcc
LD := gcc


INCLUDE_DIR := include
SOURCE_DIR := src

STRUCTURE_DIR := structures

OBJECT_DIR := obj
RESOURCES_DIR := res
TARGET := program
TARGET_DIR := bin
TARGET_SRC_DIR := $(TARGET_DIR)/src

SOURCES := $(shell find $(SOURCE_DIR) -type f -name *.c)
OBJECTS := $(patsubst $(SOURCE_DIR)/%, $(OBJECT_DIR)/%, $(SOURCES:.c=.o))

CFLAGS := -Wall -g
LFLAGS := -ldl
INC := -I $(INCLUDE_DIR) -I /usr/local/include
INC_DEP := -I $(INCLUDE_DIR)

all: directories $(TARGET)

remake: clean all

clean:
	@$(RM) -rf $(OBJECT_DIR)
	@$(RM) -rf $(TARGET_DIR)

directories:
	@mkdir -p $(OBJECT_DIR)
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(TARGET_SRC_DIR)
	@cp $(INCLUDE_DIR)/$(STRUCTURE_DIR) $(TARGET_SRC_DIR) -r
	@cp $(SOURCE_DIR)/$(STRUCTURE_DIR) $(TARGET_SRC_DIR) -r
	@cp $(RESOURCES_DIR)/* $(TARGET_DIR) -r

-include $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET_DIR)/$(TARGET) $^ $(LFLAGS)

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INC_DEP) -MM $(SOURCE_DIR)/$*.c > $(OBJECT_DIR)/$*.d
	@cp -f $(OBJECT_DIR)/$*.d $(OBJECT_DIR)/$*.d.tmp
	@sed -e 's|.*:|$(OBJECT_DIR)/$*.o:|' < $(OBJECT_DIR)/$*.d.tmp > $(OBJECT_DIR)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(OBJECT_DIR)/$*.d.tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(OBJECT_DIR)/$*.d
	@rm -f $(OBJECT_DIR)/$*.d.tmp

.PHONY: all remake clean directories
