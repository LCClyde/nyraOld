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
#ifndef NYRA_SPRITE_H_
#define NYRA_SPRITE_H_

#include <memory>
#include <SFML/Graphics.hpp>

namespace nyra
{
/*
 *  \class Sprite
 *  \brief A lite wrapper around SFML sprites. This also keeps the texture
 *         in scope.
 */
class Sprite
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an SFML sprite under the hood.
     *
     *  \param pathname The location of the texture on disk.
     */
    Sprite(const std::string& pathname);

    /*
     *  \func get
     *  \brief Get the underlying SFML sprite.
     *
     *  \return The SFML sprite.
     */
    inline const sf::Sprite& get() const
    {
        return mSprite;
    }

    /*
     *  \func get
     *  \brief Get the underlying SFML sprite.
     *
     *  \return The SFML sprite.
     */
    inline sf::Sprite& get()
    {
        return mSprite;
    }

private:
    sf::Sprite mSprite;
    std::shared_ptr<sf::Texture> mTexture;
};
}

#endif