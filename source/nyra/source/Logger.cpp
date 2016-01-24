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
#include <nyra/Logger.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <sstream>

namespace
{
//===========================================================================//
std::string currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

//===========================================================================//
nyra::Logger globalLogger;
}

namespace nyra
{
//===========================================================================//
Logger::Logger() :
    mLevel(NULL_LOGGER)
{
}

//===========================================================================//
void Logger::registerLogger(Level level, const std::string& pathname)
{
    globalLogger.mLevel = level;

    if (!pathname.empty())
    {
        if (globalLogger.mOutStream.is_open())
        {
            globalLogger.mOutStream.close();
        }
        globalLogger.mOutStream.open(pathname);
    }
    globalLogger.logInfo("Registered logger");
}

//===========================================================================//
void Logger::log(Level level,
                 const std::string& prefix,
                 const std::string& message)
{
    if (level < mLevel)
    {
        std::cout << "Failed: " << level << " " << mLevel << " " << message << "\n";
        return;
    }

    const std::string output =
            currentDateTime() + " " + prefix + ": " + message + "\n";
    if (mOutStream.is_open())
    {
        mOutStream << output;
    }
    std::cout << output;
}

//===========================================================================//
Logger& Logger::getRegisteredLogger()
{
    return globalLogger;
}

//===========================================================================//
void Logger::debug(const std::string& message)
{
    globalLogger.logDebug(message);
}

//===========================================================================//
void Logger::info(const std::string& message)
{
    globalLogger.logInfo(message);
}

//===========================================================================//
void Logger::warn(const std::string& message)
{
    globalLogger.logWarn(message);
}

//===========================================================================//
void Logger::error(const std::string& message)
{
    globalLogger.logError(message);
}
}