cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

project(CrossEngine_Examples_HelloWorld)


set(
        BUILD_SRC
        HelloWorld.cpp
)

set(
        BUILD_INCLUDE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
        BUILD_INCLUDES
        HelloWorld.hpp
)

add_executable(CrossEngine_Examples_HelloWorld ${BUILD_SRC} ${BUILD_INCLUDES})

target_link_libraries(
        CrossEngine_Examples_HelloWorld PUBLIC CrossEngine
)

message(STATUS "Loaded CrossEngine_Examples_HelloWorld")