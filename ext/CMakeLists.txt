cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

project(CrossEngine_Dependencies)



add_library(
        CrossEngine_Dependencies INTERFACE
)

add_subdirectory(glfw/)
add_subdirectory(physfs/)
add_subdirectory(spdlog/)

target_link_libraries(
        CrossEngine_Dependencies
        INTERFACE spdlog
        INTERFACE physfs
        INTERFACE glfw
)

if (CROSSENGINE_BUILD_TESTS)
    add_subdirectory(catch2/)
    target_link_libraries(
            CrossEngine_Dependencies
            INTERFACE Catch
    )
endif(CROSSENGINE_BUILD_TESTS)

message(STATUS "Loaded CrossEngine_Dependencies")