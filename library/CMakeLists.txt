cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

project(CrossEngine_Library)

set(
        LIBRARY_SOURCE
        # Utilities
        src/CrossEngine/Util/Util.cpp
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
        src/CrossEngine/Window/WindowManager.cpp
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
        includes/CrossEngine/Window/WindowManager.hpp
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

message(STATUS "Loaded CrossEngine_Library")