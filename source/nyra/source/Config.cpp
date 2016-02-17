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
#include <nyra/Config.h>
#include <nyra/Constants.h>

namespace
{
static const bool DEBUG = false;
static const std::string DATA_DIR(nyra::Constants::APP_PATH + "../data/");
static const double FRAMES_PER_SECOND = 60.0;
static const std::string TITLE = "Nyra Engine";
static const nyra::Vector2 WINDOW_POSITION(0.0, 0.0);
static const nyra::Vector2 WINDOW_SIZE(1920, 1080);
static const bool FULLSCREEN = false;
static const bool VSYNC = false;
static const nyra::Vector2 GRAVITY(0.0, 200.0);
static const std::string DEFAULT_MAP("");
}

namespace nyra
{
//===========================================================================//
Config::Config() :
    debug(DEBUG),
    dataDir(DATA_DIR),
    framesPerSecond(FRAMES_PER_SECOND),
    title(TITLE),
    windowPosition(WINDOW_POSITION),
    windowSize(WINDOW_SIZE),
    fullscreen(FULLSCREEN),
    vsync(VSYNC),
    gravity(GRAVITY),
    defaultMap(DEFAULT_MAP)
{
}
}
