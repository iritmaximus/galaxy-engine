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
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.91.9
)

FetchContent_MakeAvailable(glfw glad imgui)


set(IMGUI_SOURCES
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)
set(IMGUI_BACKEND_SOURCES
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

set(SOURCES
    src/galaxy.cpp
    src/gwindow.cpp
    src/grenderer.cpp
    src/gmenu.cpp
    src/gconfig.cpp
    src/logger.cpp
    src/gshader.cpp
    src/vertex.cpp
    src/todo.cpp
    ${GLAD_OUT_DIR}/src/glad.c
    ${IMGUI_SOURCES}
    ${IMGUI_BACKEND_SOURCES}
)

set(GLAD_PROFILE "core" CACHE STRING "glad profile (core or compatibility)")
set(GLAD_API "gl=3.3" CACHE STRING "glad api version")

configure_file(include/env-vars.h.in ${CMAKE_BINARY_DIR}/generated/include/env-vars.h)
set(INCLUDE_DIRS
    ${CMAKE_BINARY_DIR}/generated/include # env-vars.h
    ${GLAD_INCLUDE_DIRS} # glad/glad.h
    ${imgui_SOURCE_DIR}
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
