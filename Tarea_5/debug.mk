# Name of the executable to be generated #
TARGET_EXECUTABLE := exec

# Compiler flags for debugging #
DEBUG_FLAGS := -g3 -Og -Wall -Wextra -Werror

# Directories for organizing files #
BUILD_DIR := ./debug

# Source directories #
SRC_DIR := ./src

# Get directories based on source file structures #
DIRECTORIES := $(shell find $(SRC_DIR) -type d)
DIRECTORIES_FLAGS := $(addprefix -I,$(DIRECTORIES))

# Compiler and Assembler files #
C_SRC_FILES := $(shell find -name '*.c')
ASM_SRC_FILES := $(shell find -name '*.asm')

# Generate Object files from source files names #
C_OBJ_FILES := $(C_SRC_FILES:%.c=$(BUILD_DIR)/%.o)
ASM_OBJ_FILES := $(ASM_SRC_FILES:%.asm=$(BUILD_DIR)/%.o)

# Build Steps #
$(BUILD_DIR)/$(TARGET_EXECUTABLE): $(C_OBJ_FILES) $(ASM_OBJ_FILES)
	gcc $^ -o $@ $(DIRECTORIES_FLAGS) $(DEBUG_FLAGS)

# Pattern rule to compile C source files into object files #
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	gcc -c $< -o $@ $(DIRECTORIES_FLAGS) $(DEBUG_FLAGS)

# Pattern rule to compile ASM source files into object files #
$(BUILD_DIR)/%.o: %.asm
	mkdir -p $(dir $@)
	nasm -g -f elf64 -F dwarf $< -o $@


.PHONY: clean
	rm -r $(BUILD_DIR)
