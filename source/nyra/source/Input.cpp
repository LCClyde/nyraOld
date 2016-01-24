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
#include <nyra/Input.h>
#include <nyra/InputConstants.h>
#include <SFML/Window.hpp>
#include <nyra/Logger.h>

namespace nyra
{
//===========================================================================//
Input::Input() :
    mKeysPrev(sf::Keyboard::KeyCount, false)
{
    Logger::info("Input initialized");
}

//===========================================================================//
void Input::registerButton(const std::string& name,
                           const std::vector<size_t>& inputs)
{
    mInputs[name] = inputs;
}

//===========================================================================//
void Input::update()
{
    for (size_t ii = 0; ii < mKeysPrev.size(); ++ii)
    {
        mKeysPrev[ii] = sf::Keyboard::isKeyPressed(
                static_cast<sf::Keyboard::Key>(ii));
    }
}

//===========================================================================//
const std::vector<size_t>& Input::getInputs(const std::string& name) const
{
    const auto& iter = mInputs.find(name);
    if (iter == mInputs.end())
    {
        throw std::runtime_error("Unable to find input: " + name);
    }

    return iter->second;
}

//===========================================================================//
bool Input::buttonPressed(const std::string& name) const
{
    const std::vector<size_t>& inputs = getInputs(name);
    for (size_t ii : inputs)
    {
        const size_t key = ii - Keyboard::KEYBOARD_OFFSET;
        if (!(mKeysPrev[key]) &&
            sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key)))
        {
            return true;
        }
    }

    return false;
}

//===========================================================================//
bool Input::buttonDown(const std::string& name) const
{
    const std::vector<size_t>& inputs = getInputs(name);
    for (size_t ii : inputs)
    {
        const size_t key = ii - Keyboard::KEYBOARD_OFFSET;
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key)))
        {
            return true;
        }
    }

    return false;
}

//===========================================================================//
bool Input::buttonReleased(const std::string& name) const
{
    const std::vector<size_t>& inputs = getInputs(name);
    for (size_t ii : inputs)
    {
        const size_t key = ii - Keyboard::KEYBOARD_OFFSET;
        if (mKeysPrev[key] &&
            !(sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key))))
        {
            return true;
        }
    }

    return false;
}
}