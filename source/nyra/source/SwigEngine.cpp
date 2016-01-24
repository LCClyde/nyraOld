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
#include <nyra/SwigEngine.h>
#include <nyra/Engine.h>

namespace
{
static nyra::Engine* engine = nullptr;
}

namespace nyra
{
//===========================================================================//
void _set_data(size_t address)
{
    if (address == 0)
    {
        throw std::runtime_error("Attempting to create a void engine.");
    }
    engine = reinterpret_cast<Engine*>(address);
}

//===========================================================================//
void _register_button(const std::string& name,
                      const std::vector<size_t>& inputs)
{
    engine->getInput().registerButton(name, inputs);
}

//===========================================================================//
bool button_pressed(const std::string& name)
{
    return engine->getInput().buttonPressed(name);
}

//===========================================================================//
bool button_released(const std::string& name)
{
    return engine->getInput().buttonReleased(name);
}

//===========================================================================//
bool button_down(const std::string& name)
{
    return engine->getInput().buttonDown(name);
}

//===========================================================================//
void log_debug(const std::string& message)
{
    engine->getLogger().logDebug(message);
}

//===========================================================================//
void log_info(const std::string& message)
{
    engine->getLogger().logInfo(message);
}

//===========================================================================//
void log_warning(const std::string& message)
{
    engine->getLogger().logWarn(message);
}

//===========================================================================//
void log_error(const std::string& message)
{
    engine->getLogger().logError(message);
}

//===========================================================================//
void log(const std::string& message)
{
    engine->getLogger().logInfo(message);
}
}
