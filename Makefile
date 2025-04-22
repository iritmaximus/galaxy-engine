CC = g++
CC_FLAGS = -O2 -Wall -Wextra -g
LD_FLAGS = $(THIRDPARTY)/bgfx/.build/linux64_gcc/bin/libbgfx-shared-libRelease.so \
		   -I$(THIRDPARTY)/glad/include -lGL -lGLU -lX11 -lpthread -ldl -lXrandr -lXi \
		   $(GLFW_FLAGS)

THIRDPARTY = thirdparty
GLFW_FLAGS = $(THIRDPARTY)/glfw/build/src/libglfw.so -I$(THIRDPARTY)/glfw/include
BGFX_HEADERS = -I$(THIRDPARTY)/bgfx/include -I$(THIRDPARTY)/bx/include -I$(THIRDPARTY)/bimg/include

SRC_DIR = src

glad.o: $(THIRDPARTY)/glad/src/glad.c
	$(CC) -c $(THIRDPARTY)/glad/src/glad.c -o $(THIRDPARTY)/glad/src/glad.o $(CC_FLAGS) $(LD_FLAGS)

all: $(SRC_DIR)/main.cpp glad.o
	$(CC) $(SRC_DIR)/main.cpp -o main $(THIRDPARTY)/glad/src/glad.o $(CC_FLAGS) $(LD_FLAGS) $(BGFX_HEADERS)
