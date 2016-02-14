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
/*
 *  \class Logger
 *  \brief Provides a common structure for logging messages that can be used
 *         both engine and script side.
 */
class Logger
{
public:
    /*
     *  \enum Level
     *  \brief Describes the minimum level of logs that should be displayed.
     *         As levels go higher previous levels will no longer be shown.
     */
    enum Level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        NULL_LOGGER
    };

    /*
     *  \func Constructor
     *  \brief Provides a default logger.
     */
    Logger();

    /*
     *  \func registerLogger
     *  \brief Sets up the global logger that is used throughout the
     *         engine. It is valid to call this multiple times if
     *         different log levels are desired.
     *
     *  \param level The minimum log level required to display messages.
     *  \param pathname The pathname to an output file. If this is blank
     *         it will not open a new file. If a previous one was one
     *         it remains open. This allows you to change logging level
     *         without interrupting the IO.
     */
    static void registerLogger(Level level, const std::string& pathname);

    /*
     *  \func getRegisteredLogger
     *  \brief Gets the global logger. In general this is for internal use
     *         only. When logging messages simply use the direct info, log,
     *         etc methods instead,
     *
     *  \return The global logger.
     */
    static Logger& getRegisteredLogger();

    /*
     *  \func debug
     *  \brief Logs a debug level message.
     *
     *  \param message The message to display. Time, message type, and new
     *         line will be added.
     */
    static void debug(const std::string& message);

    /*
     *  \func info
     *  \brief Logs an info level message.
     *
     *  \param message The message to display. Time, message type, and new
     *         line will be added.
     */
    static void info(const std::string& message);

    /*
     *  \func warn
     *  \brief Logs a warning level message.
     *
     *  \param message The message to display. Time, message type, and new
     *         line will be added.
     */
    static void warn(const std::string& message);

    /*
     *  \func error
     *  \brief Logs an error level message.
     *
     *  \param message The message to display. Time, message type, and new
     *         line will be added.
     */
    static void error(const std::string& message);

    /*
     *  \func debug
     *  \brief Logs a debug level message.
     *
     *  \param message The message to display. Time, message type, and new
     *         line will be added.
     */
    void logDebug(const std::string& message)
    {
        log(DEBUG, "DEBUG", message);
    }

    /*
     *  \func info
     *  \brief Logs an info level message.
     *
     *  \param message The message to display. Time, message type, and new
     *         line will be added.
     */
    void logInfo(const std::string& message)
    {
        log(INFO, "INFO", message);
    }

    /*
     *  \func warn
     *  \brief Logs a warning level message.
     *
     *  \param message The message to display. Time, message type, and new
     *         line will be added.
     */
    void logWarn(const std::string& message)
    {
        log(WARN, "WARNING", message);
    }

    /*
     *  \func error
     *  \brief Logs an error level message.
     *
     *  \param message The message to display. Time, message type, and new
     *         line will be added.
     */
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
