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
#ifndef NYRA_CONSTANTS_H_
#define NYRA_CONSTANTS_H_

#include <string>

namespace nyra
{
/*
 *  \class Constants
 *  \brief A class to hold commonly used constants.
 */
class Constants
{
public:
    /*
     *  \const APP_PATH
     *  \brief The absolute path to where the application is located.
     */
    static const std::string APP_PATH;

    /*
     *  \const DEGREES_TO_RADIANS
     *  \brief Value used to convert degreees to radains.
     */
    static const double DEGREES_TO_RADIANS;

    /*
     *  \const RADIANS_TO_DEGREES
     *  \brief Value used to convert radians to degrees.
     */
    static const double RADIANS_TO_DEGREES;

    /*
     *  \const PIXELS_PER_METER
     *  \brief The number of pixels per physics meter.
     */
    static const double PIXELS_PER_METER;

    /*
     *  \const METERS_PER_PIXEL
     *  \brief The number of physics meters per pixel.
     */
    static const double METERS_PER_PIXEL;
};
}

#endif
