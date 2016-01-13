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
include(ExternalProject)
cmake_minimum_required(VERSION 2.8.12.2)

#TODO: Only set this if the caller did not set it
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/../install)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

#TODO: Hack, I should remove this
set(CMAKE_PREFIX_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} {CMAKE_PREFIX_PATH})

ExternalProject_Add(
        SFML_PROJECT
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        PREFIX ${CMAKE_BINARY_DIR}/sfml/
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX})

ExternalProject_Add(
        TGUI_PROJECT
        GIT_REPOSITORY https://github.com/texus/TGUI.git
        PREFIX ${CMAKE_BINARY_DIR}/tgui/
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX})

ExternalProject_Add(
        RAPID_JSON_PROJECT
        GIT_REPOSITORY https://github.com/miloyip/rapidjson.git
        PREFIX ${CMAKE_BINARY_DIR}/rapid_json/
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX})

ExternalProject_Add(
        BOX2D_PROJECT
        GIT_REPOSITORY https://github.com/erincatto/Box2D.git
        PREFIX ${CMAKE_BINARY_DIR}/box2d/
        PATCH_COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_BINARY_DIR}/box2d_patch.txt" <SOURCE_DIR>/CMakeLists.txt
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -DBOX2D_BUILD_EXAMPLES=OFF)
