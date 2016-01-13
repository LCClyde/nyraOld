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
#include <nyra/Graphics.h>
#include <iostream>

namespace nyra
{
//===========================================================================//
Graphics::Graphics(const std::string& title,
                   const Vector2& position,
                   const Vector2& size,
                   bool fullscreen,
                   bool vsync) :
    mFrames(0),
    mWindowTitle(title),
    mWindow(sf::VideoMode(size.x, size.y), mWindowTitle + " 0 FPS",
            fullscreen ? (sf::Style::Fullscreen) :
                         (sf::Style::Close | sf::Style::Titlebar))
{
    mWindow.setPosition(position.toThirdParty<sf::Vector2i>());
    mWindow.setVerticalSyncEnabled(vsync);
}

//===========================================================================//
bool Graphics::clear()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
            return false;
        }
    }

    // clear the window with black color
    mWindow.clear(sf::Color::Black);
    return true;
}

//===========================================================================//
void Graphics::render()
{
    // Render all sprites
    for (auto& sprite : mSprites)
    {
        mWindow.draw(sprite.get());
    }

}

//===========================================================================//
void Graphics::present()
{
    // end the current frame
    mWindow.display();

    // Check if one second has passed
    ++mFrames;
    if (mClock.getElapsedTime().asSeconds() >= 1.0)
    {
        mWindow.setTitle(mWindowTitle + " " + std::to_string(mFrames) + " FPS");
        mClock.restart();
        mFrames = 0;
    }
}

//===========================================================================//
Sprite& Graphics::addSprite(const std::string& pathname)
{
    mSprites.push_back(Sprite(pathname));
    return mSprites.back();
}
}