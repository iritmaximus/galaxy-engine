cmake_minimum_required(VERSION 4.0)
project(galaxy-engine C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

# creates compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Googletest (aka gtest)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  bgfx
  URL https://github.com/bkaradzic/bgfx.cmake/releases/download/v1.129.8866-492/bgfx.cmake.v1.129.8866-492.zip
)
FetchContent_Declare(
  glfw
  URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
)
FetchContent_MakeAvailable(glfw bgfx)


set(SOURCES
    src/galaxy.cpp
    src/gwindow.cpp
    src/grenderer.cpp
    src/logger.cpp
    src/gshader.cpp
    src/vertex.cpp
    src/todo.cpp
)

# Includes bgfx/src for #include <bgfx_shader.sh> inside shaders
set(BGFX_SHADER_INCLUDE_PATH "${BGFX_DIR}/src" CACHE STRING "bgfx include path")
set(GALAXY_SHADER_BIN_DIR "${CMAKE_BINARY_DIR}/generated/shaders" CACHE STRING "Shader install location")

set(SHADER_SOURCES
    src/shaders/v_simple.sc
    src/shaders/f_simple.sc
)

bgfx_compile_shaders(
    TYPE VERTEX
    SHADERS src/shaders/v_simple.sc
    VARYING_DEF ${CMAKE_SOURCE_DIR}/src/shaders/varying.def.sc
    OUTPUT_DIR ${CMAKE_BINARY_DIR}/generated/shaders
)

bgfx_compile_shaders(
    TYPE FRAGMENT
    SHADERS src/shaders/f_simple.sc
    VARYING_DEF ${CMAKE_SOURCE_DIR}/src/shaders/varying.def.sc
    OUTPUT_DIR ${CMAKE_BINARY_DIR}/generated/shaders
)

configure_file(include/env-vars.h.in ${CMAKE_BINARY_DIR}/generated/include/env-vars.h)

set(INCLUDE_DIRS
    ${BGFX_DIR}/include
    ${BX_DIR}/include
    ${CMAKE_BINARY_DIR}/generated/include # env-vars.h
)

add_library(galaxy-engine-lib ${SOURCES} ${SHADER_SOURCES})
add_executable(galaxy-engine src/main.cpp)

target_include_directories(galaxy-engine       PRIVATE include ${INCLUDE_DIRS})
target_include_directories(galaxy-engine-lib   PRIVATE include ${INCLUDE_DIRS})
target_link_libraries(galaxy-engine galaxy-engine-lib bgfx glfw)



# Testing
enable_testing()

set(TESTING_SOURCES
    test/todo.cpp
    ${SOURCES}
)

add_executable(tests ${TESTING_SOURCES})

target_link_libraries(
    tests
    GTest::gtest_main
    bgfx
    glfw
)

target_include_directories(tests PRIVATE include ${INCLUDE_DIRS})
include(GoogleTest)
gtest_discover_tests(tests)
