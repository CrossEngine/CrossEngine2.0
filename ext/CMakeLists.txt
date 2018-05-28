cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

project(CrossEngine_Dependencies)



add_library(
        CrossEngine_Dependencies INTERFACE
)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(glfw/)

set(PHYSFS_BUILD_TEST OFF)
add_subdirectory(physfs/)
add_subdirectory(spdlog/)
#add_subdirectory(popl/)

target_link_libraries(
        CrossEngine_Dependencies
        INTERFACE spdlog
        INTERFACE physfs
        INTERFACE glfw
)

target_include_directories(
        CrossEngine_Dependencies
        INTERFACE popl/include
        INTERFACE physfs/src
)

if (CROSSENGINE_BUILD_TESTS)
    add_subdirectory(catch2/)
    target_link_libraries(
            CrossEngine_Dependencies
            INTERFACE Catch
    )
endif(CROSSENGINE_BUILD_TESTS)

message(STATUS "Loaded CrossEngine_Dependencies")