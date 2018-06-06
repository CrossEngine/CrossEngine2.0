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
set(BUILD_SHARED_LIBS ON)
add_subdirectory(glfw/)

set(PHYSFS_BUILD_TEST OFF)
set(PHYSFS_INSTALL OFF)
add_subdirectory(physfs/)
add_subdirectory(spdlog/)
#add_subdirectory(popl/)

set(GLAD_PROFILE "core")
set(GLAD_API "gl=4.6")
set(GLAD_GENERATOR "c")
set(GLAD_EXTENSIONS "")
set(GLAD_SPEC "gl")
set(GLAD_NO_LOADER ON)
set(GLAD_INSTALL OFF)
add_subdirectory(glad/)

add_subdirectory(glm/)

target_link_libraries(
        CrossEngine_Dependencies
        INTERFACE spdlog
        INTERFACE physfs
        INTERFACE glfw
        INTERFACE glad
        INTERFACE glm
)

target_include_directories(
        CrossEngine_Dependencies
        INTERFACE popl/include
        INTERFACE physfs/src
        INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/glad/include/
)

if (CROSSENGINE_BUILD_TESTS)
    add_subdirectory(catch2/)
    target_link_libraries(
            CrossEngine_Dependencies
            INTERFACE Catch
    )
endif(CROSSENGINE_BUILD_TESTS)

message(STATUS "Loaded CrossEngine_Dependencies")