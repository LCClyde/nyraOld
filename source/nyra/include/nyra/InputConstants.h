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
#ifndef NYRA_INPUT_CONSTANTS_H_
#define NYRA_INPUT_CONSTANTS_H_

namespace nyra
{
/*
 *  \class Keyboard
 *  \brief Used to hold keyboard specific information for interfacing with
 *         SFML keyboards.
 */
class Keyboard
{
public:
    /*
     *  \enum Key
     *  \brief Gives a nyra value for each key. These are ordered the same
     *         as SFML to make it easy to translate between the two.
     */
    enum Key
    {
        KEYBOARD_OFFSET = 1000,
        A = KEYBOARD_OFFSET,     ///< The A key
        B,            ///< The B key
        C,            ///< The C key
        D,            ///< The D key
        E,            ///< The E key
        F,            ///< The F key
        G,            ///< The G key
        H,            ///< The H key
        I,            ///< The I key
        J,            ///< The J key
        K,            ///< The K key
        L,            ///< The L key
        M,            ///< The M key
        N,            ///< The N key
        O,            ///< The O key
        P,            ///< The P key
        Q,            ///< The Q key
        R,            ///< The R key
        S,            ///< The S key
        T,            ///< The T key
        U,            ///< The U key
        V,            ///< The V key
        W,            ///< The W key
        X,            ///< The X key
        Y,            ///< The Y key
        Z,            ///< The Z key
        NUM_0,         ///< The 0 key
        NUM_1,         ///< The 1 key
        NUM_2,         ///< The 2 key
        NUM_3,         ///< The 3 key
        NUM_4,         ///< The 4 key
        NUM_5,         ///< The 5 key
        NUM_6,         ///< The 6 key
        NUM_7,         ///< The 7 key
        NUM_8,         ///< The 8 key
        NUM_9,         ///< The 9 key
        ESCAPE,       ///< The Escape key
        L_CONTROL,     ///< The left Control key
        L_SHFIT,       ///< The left Shift key
        L_ALT,         ///< The left Alt key
        L_SYSTEM,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
        R_CONTROL,     ///< The right Control key
        R_SHIFT,       ///< The right Shift key
        R_ALT,         ///< The right Alt key
        R_SYSTEM,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
        MENU,         ///< The Menu key
        L_BRACKET,     ///< The [ key
        R_BRACKET,     ///< The ] key
        SEMICOLON,    ///< The ; key
        COMMA,        ///< The , key
        PERIOD,       ///< The . key
        QUOTE,        ///< The ' key
        SLASH,        ///< The / key
        BACKSLASH,    ///< The \ key
        TILDE,        ///< The ~ key
        EQUAL,        ///< The = key
        DASH,         ///< The - key
        SPACE,        ///< The Space key
        RETURN,       ///< The Return key
        BACKSPACE,    ///< The Backspace key
        TAB,          ///< The Tabulation key
        PAGE_UP,       ///< The Page up key
        PAGE_DOWN,     ///< The Page down key
        END,          ///< The End key
        HOME,         ///< The Home key
        INSERT,       ///< The Insert key
        DELETE,       ///< The Delete key
        ADD,          ///< The + key
        SUBTRACT,     ///< The - key
        MULTIPLY,     ///< The * key
        DIVIDE,       ///< The / key
        LEFT,         ///< Left arrow
        RIGHT,        ///< Right arrow
        UP,           ///< Up arrow
        DOWN,         ///< Down arrow
        NUMPAD_0,      ///< The numpad 0 key
        NUMPAD_1,      ///< The numpad 1 key
        NUMPAD_2,      ///< The numpad 2 key
        NUMPAD_3,      ///< The numpad 3 key
        NUMPAD_4,      ///< The numpad 4 key
        NUMPAD_5,      ///< The numpad 5 key
        NUMPAD_6,      ///< The numpad 6 key
        NUMPAD_7,      ///< The numpad 7 key
        NUMPAD_8,      ///< The numpad 8 key
        NUMPAD_9,      ///< The numpad 9 key
        F1,           ///< The F1 key
        F2,           ///< The F2 key
        F3,           ///< The F3 key
        F4,           ///< The F4 key
        F5,           ///< The F5 key
        F6,           ///< The F6 key
        F7,           ///< The F7 key
        F8,           ///< The F8 key
        F9,           ///< The F9 key
        F10,          ///< The F10 key
        F11,          ///< The F11 key
        F12,          ///< The F12 key
        F13,          ///< The F13 key
        F14,          ///< The F14 key
        F15,          ///< The F15 key
        PAUSE,        ///< The Pause key
    };
};
}

#endif