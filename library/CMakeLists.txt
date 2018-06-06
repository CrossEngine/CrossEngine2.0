cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

project(CrossEngine_Library)

set(
        LIBRARY_SOURCE
        # Utilities
        src/CrossEngine/Util/Util.cpp
        src/CrossEngine/Util/Math.cpp
        src/CrossEngine/Util/Clock.cpp
        src/CrossEngine/Util/Memory.cpp
        src/CrossEngine/Util/Containers.cpp

        # Logging
        src/CrossEngine/Logging/Logging.cpp

        # Application
        src/CrossEngine/Application/Application.cpp

        # Event Bus
        src/CrossEngine/EventBus/Event.cpp
        src/CrossEngine/EventBus/Events.cpp
        src/CrossEngine/EventBus/EventBus.cpp
        src/CrossEngine/EventBus/EventHandler.cpp

        # IO
        src/CrossEngine/IO/IOFile.cpp
        src/CrossEngine/IO/IOSystem.cpp
        src/CrossEngine/IO/IOStream.cpp

        # Window
        src/CrossEngine/Window/Window.cpp
        src/CrossEngine/Window/WindowEvents.cpp
        src/CrossEngine/Window/WindowManager.cpp

        # Configuration
        src/CrossEngine/Config/Configuration.cpp
        src/CrossEngine/Config/ConfigurationManager.cpp

        # Render
        src/CrossEngine/Render/Shader.cpp
        src/CrossEngine/Render/Renderer.cpp
        src/CrossEngine/Render/RenderEvents.cpp
        src/CrossEngine/Render/RenderObject.cpp

        # Render OpenGL
        src/CrossEngine/Render/OpenGL/Model.cpp
        src/CrossEngine/Render/OpenGL/Shader.cpp
        src/CrossEngine/Render/OpenGL/Material.cpp
        src/CrossEngine/Render/OpenGL/OpenGLRenderer.cpp
)

set(
        LIBRARY_INCLUDE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_BINARY_DIR}/includes
)

set(
        LIBRARY_INCLUDES
        includes/CrossEngine.hpp
        # Utilities
        includes/CrossEngine/Util/Util.hpp
        includes/CrossEngine/Util/Math.hpp
        includes/CrossEngine/Util/Clock.hpp
        includes/CrossEngine/Util/Memory.hpp
        includes/CrossEngine/Util/Containers.hpp

        # Logging
        includes/CrossEngine/Logging/Logging.hpp

        # Application
        includes/CrossEngine/Application/Application.hpp

        # Event Bus
        includes/CrossEngine/EventBus/Event.hpp
        includes/CrossEngine/EventBus/Events.hpp
        includes/CrossEngine/EventBus/EventBus.hpp
        includes/CrossEngine/EventBus/EventHandler.hpp

        # IO
        includes/CrossEngine/IO/IOFile.hpp
        includes/CrossEngine/IO/IOSystem.hpp
        includes/CrossEngine/IO/IOStream.hpp

        # Window
        includes/CrossEngine/Window/Window.hpp
        includes/CrossEngine/Window/WindowEvents.hpp
        includes/CrossEngine/Window/WindowManager.hpp

        # Configuration
        includes/CrossEngine/Config/Configuration.hpp
        includes/CrossEngine/Config/ConfigurationManager.hpp

        # Render
        includes/CrossEngine/Render/Shader.hpp
        includes/CrossEngine/Render/Renderer.hpp
        includes/CrossEngine/Render/RenderEvents.hpp
        includes/CrossEngine/Render/RenderObject.hpp

        # Render OpenGL
        includes/CrossEngine/Render/OpenGL/Model.hpp
        includes/CrossEngine/Render/OpenGL/Shader.hpp
        includes/CrossEngine/Render/OpenGL/Material.hpp
        includes/CrossEngine/Render/OpenGL/OpenGLRenderer.hpp
        includes/CrossEngine/Render/OpenGL/OpenGL.hpp
)

add_library(
        CrossEngine_Library SHARED ${LIBRARY_SOURCE} ${LIBRARY_INCLUDES}
)

set_target_properties(
        CrossEngine_Library PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        DEFINE_SYMBOL "CrossEngine_Library_Exports"
)

include_directories(${LIBRARY_INCLUDE_DIR})
target_include_directories(
        CrossEngine_Library
        PUBLIC ${LIBRARY_INCLUDE_DIR}
)

target_link_libraries(
        CrossEngine_Library
        CrossEngine_Dependencies
        CrossEngine_Config
)

find_library(
        PThread
        NAMES pthread libwinpthread-1
)

if (NOT PThread)
    message(STATUS "Could not find Pthread")
else(NOT PThread)
    message(STATUS ${PThread})
    target_link_libraries(
            CrossEngine_Library
            ${PThread}
    )
endif()

if (MINGW)

    find_library(
            GCC_S_SEH
            NAMES libgcc_s_seh-1
    )

    find_library(
            STD_CPP
            NAMES libstdc++-6
    )

    add_custom_command(
            TARGET CrossEngine_Library
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PThread} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GCC_S_SEH} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${STD_CPP} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
endif()

message(STATUS "Loaded CrossEngine_Library")