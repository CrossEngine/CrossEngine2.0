cmake_minimum_required(VERSION 3.9)

project(CrossEngine_Config)

include(version)
include(buildnumber)

configure_file(
        cmake/config.h.in
        ${CMAKE_BINARY_DIR}/includes/CrossEngine/config.h
        @ONLY
)

configure_file(
        cmake/config.c.in
        ${CMAKE_BINARY_DIR}/src/CrossEngine/config.c
        @ONLY
)


add_library(
        CrossEngine_Config STATIC
        ${CMAKE_BINARY_DIR}/src/CrossEngine/config.c
        ${CMAKE_BINARY_DIR}/includes/CrossEngine/config.h
)


set_target_properties(
        CrossEngine_Config PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        DEFINE_SYMBOL "CrossEngine_Library_Exports"
)

include_directories(${CMAKE_BINARY_DIR}/includes)
target_include_directories(
        CrossEngine_Config
        PUBLIC ${CMAKE_BINARY_DIR}/includes
)