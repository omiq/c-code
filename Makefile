SRC_DIR = src
BUILD_DIR = build
CC = /usr/bin/gcc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_NAME = game
INCLUDE_PATHS = -Iinclude/SDL2
LIBRARY_PATHS = -Llib
COMPILER_FLAGS = -rpath @executable_path/
LINKER_FLAGS = -F/Library/Frameworks -framework SDL2

all:
	$(CC) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS)
 