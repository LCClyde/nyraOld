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
#ifndef NYRA_INPUT_H_
#define NYRA_INPUT_H_

#include <string>
#include <vector>
#include <unordered_map>

namespace nyra
{
/*
 *  \class Input
 *  \brief Provides a single interface for managing input. Input is registered
 *         with a string and then queried using that string. This seperates
 *         the keys from actions and makes it easier to allow user defined
 *         input.
 */
class Input
{
public:
    /*
     *  \func Constructor
     *  \brief Initializes an Input object.
     */
    Input();

    /*
     *  \func registerInput
     *  \brief Registers a string to a list of input. This string can then
     *         be used to queury the various states of input.
     *
     *  \param name The name of the input. This is used for later querying
     *         state.
     *  \param inputs The list of inputs. Use the InputConstants to handle
     *         the values.
     */
    void registerInput(const std::string& name,
                       const std::vector<size_t>& inputs);

    /*
     *  \func buttonPressed
     *  \brief Used to determine if a button was pressed. Pressed is defined as
     *         being held down on this frame but not on the previous frame.
     *
     *  \param name The name of the input used during registration.
     *  \return True if the button was pressed this frame.
     */
    bool buttonPressed(const std::string& name) const;

    /*
     *  \func buttonDown
     *  \brief Used to determine if a button is being held down. Held down is
     *         defined as currently being pressed. It can be down for
     *         consecutive frames.
     *
     *  \param name The name of the input used during registration.
     *  \return True if the button is down this frame.
     */
    bool buttonDown(const std::string& name) const;

    /*
     *  \func buttonReleased
     *  \brief Used to determine if a button was released. Released is defined
     *         as being down the previous frame but not down this frame.
     *
     *  \param name The name of the input used during registration.
     *  \return True if the button was released this frame.
     */
    bool buttonReleased(const std::string& name) const;

    /*
     *  \func update
     *  \brief Updates the state of all the input devices. This should only
     *         be called internally.
     */
    void update();

private:
    const std::vector<size_t>& getInputs(const std::string& name) const;

    std::vector<bool> mKeysPrev;
    std::unordered_map<std::string, std::vector<size_t> > mInputs;
};
}

#endif

