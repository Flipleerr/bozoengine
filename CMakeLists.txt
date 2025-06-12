# this is just the example CMakeLists.txt from the SDL wiki, but it works fine enough
cmake_minimum_required(VERSION 3.20)
project(bozoengine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(thirdparty/SDL EXCLUDE_FROM_ALL)

add_executable(bozoengine src/main.c)

target_link_libraries(bozoengine PRIVATE SDL3::SDL3)