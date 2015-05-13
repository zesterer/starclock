#Specify the cmake version being used
cmake_minimum_required(VERSION 2.6)

#Require pkg-config to continue
find_package(PkgConfig REQUIRED)

#Add a version number
set (STARCLOCK_VERSION_MAJOR 0)
set (STARCLOCK_VERSION_MINOR 1)

#Name of the project
project(starclock)

#Tell the compiler to include -std=c++11
add_definitions(-std=c++11 -Wall)

#Libraries that can be imported with pkg-config
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

#Define a configuration file used by cmake
configure_file("${PROJECT_SOURCE_DIR}/src/main.h.in" "${PROJECT_BINARY_DIR}/main.h")

#Add a location for a search path for headers
include_directories("${PROJECT_BINARY_DIR}")

#All the directories containing header files
include_directories(
"${PROJECT_SOURCE_DIR}/src/core/"
"${PROJECT_SOURCE_DIR}/src/common/"
"${PROJECT_SOURCE_DIR}/src/render/"
"${PROJECT_SOURCE_DIR}/src/render/structures/"
)

set(SOURCE_FILES
src/main.cpp
src/core/application.cpp
src/common/out.cpp
src/core/window.cpp
src/render/scene.cpp
src/render/camera.cpp
src/render/entity.cpp
src/render/structures/model.cpp
src/render/structures/mesh.cpp
src/render/structures/texture.cpp
src/render/structures/shaders.cpp
src/render/structures/light.cpp
)

#Take the code and turn it into the executable
add_executable(starclock ${SOURCE_FILES})

#Link the final executable to the needed libraries
target_link_libraries(starclock glfw ${GLFW_LIBRARIES})
target_link_libraries(starclock glbinding ${GLBINDING_LIBRARIES})
