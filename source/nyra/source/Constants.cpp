/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Clyde Stanfield
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
#include <nyra/Constants.h>
#include <cstring>

#ifdef __linux__
#include <limits.h>
#include <unistd.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

namespace
{
//! TODO: Implement this for other platforms
#ifdef __linux__
std::string getApplicationPath()
{
    char buff[PATH_MAX];
    memset(buff, 0, PATH_MAX);
    ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
    const std::string ret(buff);
    const size_t find = ret.find_last_of("/\\");
    return find != std::string::npos ? ret.substr(0, find + 1) : ret;
}
#endif
}

namespace nyra
{
const std::string Constants::APP_PATH(getApplicationPath());
const double Constants::DEGREES_TO_RADIANS = M_PI / 180.0;
const double Constants::PIXELS_PER_METER = 16.0;
const double Constants::METERS_PER_PIXEL = 1.0 / Constants::PIXELS_PER_METER;
}