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
#ifndef NYRA_GRAPHICS_H_
#define NYRA_GRAPHICS_H_

#include <string>
#include <memory>
#include <nyra/Vector2.h>
#include <nyra/Sprite.h>
#include <SFML/Graphics.hpp>

namespace nyra
{
/*
 *  \class Graphics
 *  \func Top level class to handle managing graphics objects.
 */
class Graphics
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the internal structure of a Graphics object.
     *
     *  \param title The title of the window.
     *  \param position The position of the window.
     *  \param size The size of the client area of the window.
     *  \param fullscreen Should the window be fullscreen?
     *  \param vsync Should the graphics use vsync?
     */
    Graphics(const std::string& title,
             const Vector2& position,
             const Vector2& size,
             bool fullscreen,
             bool vsync);

    /*
     *  \func clear
     *  \brief Updates the window and clears the buffer to prepare for drawing.
     *
     *  \return False if the window was closed. If it was closed then drawing
     *          should not be done.
     */
    bool clear();

    /*
     *  \func render
     *  \brief Renders all managed sprites to the screen.
     */
    void render();

    /*
     *  \func present
     *  \brief Updates the window with the contents of the back buffer.
     */
    void present();

    /*
     *  \func reset
     *  \brief Resets the state of the graphics to when it was first created.
     */
    inline void reset()
    {
        mSprites.clear();
    }

    /*
     *  \func getVsyncFlag
     *  \brief Returns whether the renderer is using vsync.
     *
     *  \return True if vsync is enabled
     */
    inline bool getVsyncFlag() const
    {
        return mVsync;
    }

    /*
     *  \func addSprite
     *  \brief Creates a new sprite object and adds it as a managed object.
     *
     *  \param pathname The full pathname to the sprite image.
     *  \return The sprite object that was created.
     */
    Sprite& addSprite(const std::string& pathname);

    /*
     *  \func getWindow
     *  \brief Gets the underlying native window object.
     *
     *  \return The SFML window.
     */
    inline sf::RenderWindow& getWindow()
    {
        return mWindow;
    }

private:
    sf::Clock mClock;
    size_t mFrames;
    const bool mVsync;

    const std::string mWindowTitle;
    sf::RenderWindow mWindow;
    std::vector<std::unique_ptr<Sprite> > mSprites;
};
}

#endif

