SRC_DIR = src
BUILD_DIR = build
CC = /usr/bin/gcc
SRC_FILES = $(SRC_DIR)/main.c #$(wildcard $(SRC_DIR)/*.c)
OBJ_NAME = game
INCLUDE_PATHS = -Iinclude/SDL2 -Iinclude/SDL2_image
LIBRARY_PATHS = -Llib
COMPILER_FLAGS = -rpath @executable_path/
LINKER_FLAGS = -Fbuild -framework SDL2 -framework SDL2_image

all:
	$(CC) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME) $(LINKER_FLAGS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) $(COMPILER_FLAGS)
 