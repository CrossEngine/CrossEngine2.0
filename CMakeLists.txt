cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(CrossEngine)

set(
        CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

option(CROSSENGINE_BUILD_TESTS "Build tests for CrossEngine" OFF)

include(config)

add_subdirectory(ext/)

add_subdirectory(library/)

add_library(CrossEngine INTERFACE)
target_link_libraries(
        CrossEngine
        INTERFACE CrossEngine_Dependencies
        INTERFACE CrossEngine_Library
)
add_definitions(-DCrossEngine_Library_Exports)

add_subdirectory(editor/)
if (CROSSENGINE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test/)
endif (CROSSENGINE_BUILD_TESTS)
add_subdirectory(examples/)

message(STATUS "Loaded CrossEngine")