cmake_minimum_required (VERSION 3.5)
project (platformer)

# Compiler options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-Wall -Wextra -pedantic-errors -O3 -g")
#	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-Weffc++)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-Weverything -Wno-c++98-compat -Wno-padded -Wno-covered-switch-default")
else()
	message(">	Warning: No flags set")
endif()

#print compiler information
message(">	Compiler: ${CMAKE_CXX_COMPILER}")
message(">	Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
message(">	standard: c++${CMAKE_CXX_STANDARD}")
message(">	Flags: ${CMAKE_CXX_FLAGS}")
message(">	Supported features:	${CMAKE_CXX_COMPILE_FEATURES}")
message("------------------------------")


# Setup project layout
set(PROJECT_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(PROJECT_SOURCE_DIR "${PROJECT_ROOT_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}")

# Application Name
set(EXECUTABLE_NAME "platformer")
# Application Version
set(Platformer_VERSION_MAJOR 0)
set(Platformer_VERSION_MINOR 0)
set(Platformer_VERSION_REVISION 1)
# OpenGL Version
set(Platformer_OPENGL_MAJOR 3)
set(Platformer_OPENGL_MINOR 3)
# Initialize platformerConfig.hpp
configure_file (
	"${PROJECT_ROOT_DIR}/config/platformerConfig.hpp.in"
	"${PROJECT_SOURCE_DIR}/platformerConfig.hpp"
)

# Add our objects to cmake
add_library(velocity STATIC ${PROJECT_SOURCE_DIR}/velocity.cpp)
add_library(dynamic STATIC ${PROJECT_SOURCE_DIR}/dynamic.cpp)
add_library(mesh STATIC ${PROJECT_SOURCE_DIR}/mesh.cpp)
add_library(shader STATIC ${PROJECT_SOURCE_DIR}/shader.cpp)
add_library(gameObjects STATIC ${PROJECT_SOURCE_DIR}/gameObjects.cpp)
add_library(gameObjectFactory ${PROJECT_SOURCE_DIR}/gameObjectFactory.cpp)
add_library(camera STATIC ${PROJECT_SOURCE_DIR}/camera.cpp)
add_library(game STATIC ${PROJECT_SOURCE_DIR}/game.cpp)

add_executable(${EXECUTABLE_NAME}
		${PROJECT_SOURCE_DIR}/platformerMain.cpp
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Link SFML 2
find_package(SFML 2 REQUIRED COMPONENTS system window audio)
if (SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(mesh ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
	target_link_libraries(shader ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
	target_link_libraries(gameObjects ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
	target_link_libraries(game ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Link OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
	message("-- Found OpenGL")
	include_directories(${OPENGL_INCLUDE_DIRS})
	target_link_libraries(mesh ${OPENGL_LIBRARIES})
	target_link_libraries(shader ${OPENGL_LIBRARIES})
	target_link_libraries(gameObjects ${OPENGL_LIBRARIES})
	target_link_libraries(game ${OPENGL_LIBRARIES})
else()
	message("-- OpenGL Not Found")
endif()

# Link GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
	message("-- Found GLEW")
	include_directories(${GLEW_INCLUDE_DIRS})
	target_link_libraries(mesh ${GLEW_LIBRARIES})
	target_link_libraries(shader ${GLEW_LIBRARIES})
	target_link_libraries(gameObjects ${GLEW_LIBRARIES})
	target_link_libraries(game ${GLEW_LIBRARIES})
endif()

# Link GLM
find_package(GLM)
if (GLM_FOUND)
	message("-- Found GLM")
	include_directories(${GLM_INCLUDE_DIRS})
endif()

# Link our files depending on their dependencies
target_link_libraries(dynamic velocity)

target_link_libraries(gameObjects dynamic)
target_link_libraries(gameObjects mesh)
target_link_libraries(gameObjects shader)

target_link_libraries(gameObjectFactory mesh)
target_link_libraries(gameObjectFactory shader)
target_link_libraries(gameObjectFactory gameObjects)

target_link_libraries(game gameObjectFactory)
target_link_libraries(game gameObjects)
target_link_libraries(game camera)

target_link_libraries(${EXECUTABLE_NAME} game)



