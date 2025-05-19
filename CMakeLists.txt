cmake_minimum_required(VERSION 4.0)
project(galaxy-engine C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

# creates compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL)

include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
)
# uses old version of glad to match with learnopengl.com
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glfw glad)

set(SOURCES
    src/galaxy.cpp
    src/gwindow.cpp
    src/grenderer.cpp
    src/logger.cpp
    src/gshader.cpp
    src/vertex.cpp
    src/todo.cpp
    ${GLAD_OUT_DIR}/src/glad.c
)

set(GLAD_PROFILE "core" CACHE STRING "glad profile (core or compatibility)")
set(GLAD_API "gl=3.3" CACHE STRING "glad api version")

configure_file(include/env-vars.h.in ${CMAKE_BINARY_DIR}/generated/include/env-vars.h)
set(INCLUDE_DIRS
    ${CMAKE_BINARY_DIR}/generated/include # env-vars.h
    ${GLAD_INCLUDE_DIRS} # glad/glad.h
)

add_library(galaxy-engine-lib ${SOURCES})
add_executable(galaxy-engine src/main.cpp)

target_include_directories(galaxy-engine       PRIVATE include ${INCLUDE_DIRS})
target_include_directories(galaxy-engine-lib   PRIVATE include ${INCLUDE_DIRS})
target_link_libraries(
  galaxy-engine
  galaxy-engine-lib
  glad
  glfw
  OpenGL
)
