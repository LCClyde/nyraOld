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
#ifndef NYRA_ENGINE_BASE_H_
#define NYRA_ENGINE_BASE_H_

#include <string>
#include <nyra/Vector2.h>

namespace nyra
{
/*
 *  \class EngineBase
 *  \brief Templated base class that can be used with any combination of
 *         specialized components.
 *
 *
 *  \tparam WindowT The Window type. This should include all methods of the
 *          WindowInterface class.
 *  \tparam GraphicsT The Graphics types. This should include all methods of
 *          the GraphicsInterface class.
 */
template <typename WindowT,
          typename GraphicsT>
class EngineBase
{
public:
    /*
     *  \fn Constructor
     *  \brief Sets up the internal structure of the engine.
     *
     *  \param windowTitle The title of the window.
     *  \param windowSize The size of the window in pixels
     *  \param windowPosition The position of the window from the top left
     *         corner in pixels.
     *  \param windowFullscreen Should the window be displayed in
     *         fullscreen mode?
     */
    EngineBase(const std::string& windowTitle = "Nyra Engine",
               const Vector2U& windowSize = Vector2U(1280, 720),
               const Vector2I& windowPosition = Vector2I(0, 0),
               bool windowFullscreen = false) :
        mWindow(windowTitle,
                windowSize,
                windowPosition,
                windowFullscreen)
    {
    }

    /*
     *  \fn run
     *  \brief Starts the engine. Note that this is a blocking function.
     */
    void run()
    {
        while (mWindow.update())
        {
            mGraphics.clear(mWindow.getHandle());
            mGraphics.present();
        }
    }

private:
    WindowT mWindow;
    GraphicsT mGraphics;
};
}

#endif
