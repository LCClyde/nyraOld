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
#include <iostream>
#include <stdexcept>
#include <memory>
#include <nyra/Logger.h>
#include <nyra/Engine.h>

int main(int argc, char** argv)
{
    try
    {
        nyra::Logger::registerLogger(nyra::Logger::DEBUG, "./log.txt");
        nyra::Engine engine;
        engine.loadMap("test");

        while (engine.update())
        {
        }

        nyra::Logger::info("Engine properly shutdown");
    }
    catch (const std::exception& ex)
    {
        nyra::Logger::error(
                std::string("Caught standard exception: ") + ex.what());
    }
    catch (...)
    {
        nyra::Logger::error("Caught unnamed exception");
    }

    return 1;
}
