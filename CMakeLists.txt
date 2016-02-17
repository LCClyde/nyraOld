#
# The MIT License (MIT)
#
# Copyright (c) 2015 Clyde Stanfield
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#
cmake_minimum_required(VERSION 2.8.12.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -fPIC")

#TODO: Only set this if the caller did not set it
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(INCLUDE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include)
set(SOURCE_DIRECTORY ${CMAKE_BINARY_DIR}/source)
set(PROJECTS_DIRECTORY ${CMAKE_BINARY_DIR}/projects)
set(EXTERNALS_DIRECTORY ${CMAKE_BINARY_DIR}/externals)
set(PYTHON_DIRECTORY ${CMAKE_INSTALL_PREFIX}/python)

#TODO: Hack, I should remove this
set(CMAKE_PREFIX_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} {CMAKE_PREFIX_PATH})

include_directories(include ${INCLUDE_DIRECTORY})
find_library(SFML_SYSTEM NAMES sfml-system PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(SFML_WINDOW NAMES sfml-window PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(SFML_GRAPHICS NAMES sfml-graphics PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(TGUI NAMES tgui PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(BOX2D NAMES Box2D PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_package(Threads)

# Find python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
message(${PYTHON_INCLUDE_DIRS})

# Build nyra library
include_directories(include ${SOURCE_DIRECTORY}/nyra/include/)
file(GLOB SOURCES ${SOURCE_DIRECTORY}/nyra/source/*.cpp)
add_library(nyra ${SOURCES})
target_link_libraries(nyra ${SFML_SYSTEM} ${SFML_WINDOW} ${SFML_GRAPHICS} ${TGUI} ${PYTHON_LIBRARIES} ${BOX2D})


# Build projects
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
file(GLOB projects RELATIVE ${PROJECTS_DIRECTORY} ${PROJECTS_DIRECTORY}/*)
foreach(dir ${projects})
    if (IS_DIRECTORY ${PROJECTS_DIRECTORY}/${dir})

        # Check for a custom cmake
        if(EXISTS ${PROJECTS_DIRECTORY}/${dir}/CMakeLists.txt)
            add_subdirectory(${PROJECTS_DIRECTORY}/${dir})
        endif()

        # Build the file
        file(GLOB files ${PROJECTS_DIRECTORY}/${dir} ${PROJECTS_DIRECTORY}/${dir}/*.cpp)
        add_executable(${dir} ${files})
        target_link_libraries(${dir} nyra)
    endif()
endforeach()

#add_custom_command(OUTPUT copyPython
#                   PRE_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy_directory
#                       ${SOURCE_DIRECTORY}/nyra/python ${PYTHON_DIRECTORY})

# Create swig files
file(MAKE_DIRECTORY ${PYTHON_DIRECTORY})
add_custom_command(
    OUTPUT swig
    PRE_BUILD
    COMMAND swig -I${CMAKE_BINARY_DIR}/source/nyra/include -outdir ${PYTHON_DIRECTORY} -o ${SOURCE_DIRECTORY}/nyra/nyra_wrap.cpp -python -c++ nyra.i)

add_custom_target(
  BuildSwig ALL
  DEPENDS swig)

#add_custom_target(
#  CopyPython ALL
#  DEPENDS copyPython BuildSwig)

# Build the swig lib
add_library(_nyra SHARED ${SOURCE_DIRECTORY}/nyra/nyra_wrap.cpp)
add_dependencies(_nyra nyra)
target_link_libraries(_nyra nyra)

