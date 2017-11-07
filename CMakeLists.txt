cmake_minimum_required (VERSION 3.5)
project (platformer)

# Compiler options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-Wall -Wextra -Weffc++ -O2")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-Weverything")
else()
	message(">	Warning: No flags set")
endif()

message(">	Compiler: ${CMAKE_CXX_COMPILER}")
message(">	Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
message(">	standard: c++${CMAKE_CXX_STANDARD}")
message(">	Flags: ${CMAKE_CXX_FLAGS}")
message(">	Supported features:	${CMAKE_CXX_COMPILE_FEATURES}")
message("------------------------------")

# Setup project layout
set(PROJECT_ROOT_DIR "${PROJECT_SOURCE_DIR}") # CS202-Group-Project
set(PROJECT_BINARY_DIR "${PROJECT_ROOT_DIR}/bin") # CS202-Group-Project/bin
set(PROJECT_SOURCE_DIR "${PROJECT_ROOT_DIR}/src") # CS202-Group-Project/src
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}) # CS202-Group-Project/bin
include_directories("${PROJECT_SOURCE_DIR}")

# Initialize platformerConfig.hpp
# Version
set(Platformer_VERSION_MAJOR 0)
set(Platformer_VERSION_MINOR 0)
set(Platformer_VERSION_REVISION 1)
configure_file (
	"${PROJECT_ROOT_DIR}/config/platformerConfig.hpp.in"
	"${PROJECT_SOURCE_DIR}/platformerConfig.hpp"
)

# Executable file name
set(EXECUTABLE_NAME "platformer")

add_executable(${EXECUTABLE_NAME} ${PROJECT_SOURCE_DIR}/platformerMain.cpp)

# Link SFML 2
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)
if (SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Link OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIRS})
	target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
endif()

