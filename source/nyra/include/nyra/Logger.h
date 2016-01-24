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
#ifndef NYRA_LOGGER_H_
#define NYRA_LOGGER_H_

#include <string>
#include <fstream>

namespace nyra
{
class Logger
{
public:
    enum Level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        NULL_LOGGER
    };

    Logger();

    static void registerLogger(Level level, const std::string& pathname);

    static Logger& getRegisteredLogger();

    static void debug(const std::string& message);

    static void info(const std::string& message);

    static void warn(const std::string& message);

    static void error(const std::string& message);

    void logDebug(const std::string& message)
    {
        log(DEBUG, "DEBUG", message);
    }

    void logInfo(const std::string& message)
    {
        log(INFO, "INFO", message);
    }

    void logWarn(const std::string& message)
    {
        log(WARN, "WARNING", message);
    }

    void logError(const std::string& message)
    {
        log(ERROR, "ERROR", message);
    }

private:
    void log(Level level,
             const std::string& prefix,
             const std::string& message);

    Level mLevel;
    std::ofstream mOutStream;
};
}

#endif
