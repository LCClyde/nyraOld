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
#ifndef NYRA_SWIG_ENGINE_H_
#define NYRA_SWIG_ENGINE_H_

#include <string>
#include <vector>
#include <nyra/Vector2.h>

namespace nyra
{
/*
 *  \func _register_input
 *  \brief Allows input to be registered from Python.
 *
 *  \param name The name of the input
 *  \param inputs The keys associated with the input.
 */
void _register_input(const std::string& name,
                     const std::vector<size_t>& inputs);

/*
 *  \func button_pressed
 *  \brief Check if a button is pressed from Python
 *
 *  \param name The name of the input
 *  \return True if the button is pressed
 */
bool button_pressed(const std::string& name);

/*
 *  \func button_released
 *  \brief Check if a button was release from Python
 *
 *  \param name The name of the input
 *  \return True if the button was released
 */
bool button_released(const std::string& name);

/*
 *  \func button_down
 *  \brief Checks if a button is down from Python
 *
 *  \param name The name of the input
 *  \return True if the button is down
 */
bool button_down(const std::string& name);

/*
 *  \func log_debug
 *  \brief Prints a debug message from Python
 *
 *  \param message The message to print
 */
void log_debug(const std::string& message);

/*
 *  \func log_info
 *  \brief Prints an info message from Python
 *
 *  \param message The message to print
 */
void log_info(const std::string& message);

/*
 *  \func log_warning
 *  \brief Prints a warning message from Python
 *
 *  \param message The message to print
 */
void log_warning(const std::string& message);

/*
 *  \func log_error
 *  \brief Prints an error message from Python
 *
 *  \param message The message to print
 */
void log_error(const std::string& message);

/*
 *  \func log
 *  \brief Convience function for log_info
 *
 *  \param message The message to print
 */
void log(const std::string& message);

/*
 *  \func _camera_track
 *  \brief Sets the camera to track an actor.
 *
 *  \param actor The memory address of the actor to track.
 *  \param offset The tracking offset in pixels.
 */
void _camera_track(size_t actor,
                   const Vector2& offset);

/*
 *  \func _set_data
 *  \brief Sets the engine instance to allow Python to use the same
 *         memory space as the game. This should only be called internally.
 *
 *  \param address The pointer address of the engine.
 */
void _set_data(size_t address);
}

#endif
