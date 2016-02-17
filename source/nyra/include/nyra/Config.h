/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#ifndef NYRA_CONFIG_H_
#define NYRA_CONFIG_H_

#include <string>


#include <string>
#include <nyra/Vector2.h>
#include <nyra/JSONReader.h>

namespace nyra
{
struct Config
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a default config object.
     */
    Config();

    /*
     *  \var debug
     *  \brief If true debug options are enabled.
     */
    bool debug;

    /*
     *  \var dataDir
     *  \brief The path to the data directory. This is where
     *         the engine expects all of its game level files.
     */
    std::string dataDir;

    /*
     *  \var framesPerSecond
     *  \brief The number of that are applied each second.
     *         If vsync is on this is ignored.
     */
    double framesPerSecond;

    /*
     *  \var title
     *  \brief The title of the window that is created. This can
     *         usually be your game title.
     */
    std::string title;

    /*
     *  \var position
     *  \brief The starting position of the window.
     */
    Vector2 windowPosition;

    /*
     *  \var size
     *  \brief The size of the window.
     */
    Vector2 windowSize;

    /*
     *  \var fullscreen
     *  \brief Should the game start in fullscreen?
     */
    bool fullscreen;

    /*
     *  \var vsync
     *  \brief Should the graphics be run with vsync on?
     */
    bool vsync;

    /*
     *  \var gravity
     *  \brief The force of gravity in meters / second squared. Note
     *         that 0, 0 is the top left of the window meaning positive Y is
     *         a downward force.
     */
    Vector2 gravity;

    /*
     *  \var defaultMap
     *  \brief The default map to load. If this is an empty string nothing
     *         is loaded.
     */
    std::string defaultMap;
};
}


#endif
