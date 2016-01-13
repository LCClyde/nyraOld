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
#ifndef NYRA_ACTOR_H_
#define NYRA_ACTOR_H_

#include <string>
#include <SFML/Graphics.hpp>
#include <nyra/Vector2.h>
#include <nyra/Script.h>
#include <nyra/Body.h>
#include <iostream>

namespace nyra
{
class Actor
{
public:
    Actor();

    void setSprite(sf::Sprite& sprite)
    {
        mSprite = &sprite;
    }

    void setScript(Script& script)
    {
        mScript = &script;
    }

    void setPhysics(Body& physics)
    {
        mPhysics = &physics;
    }

    void setPosition(const Vector2& position)
    {
        if (mSprite)
        {
            mSprite->setPosition(position.toThirdParty<sf::Vector2f>());
        }
        if (mPhysics)
        {
            mPhysics->setPosition(position);
        }
    }

    Vector2 getPosition() const
    {
        if (mSprite)
        {
            return mSprite->getPosition();
        }
        return Vector2();
    }

    void updateGraphicsWithPhysics()
    {
        if (mSprite && mPhysics)
        {
            mSprite->setPosition(
                    mPhysics->getPosition().toThirdParty<sf::Vector2f>());
        }
    }

    bool hasSprite() const
    {
        return mSprite != nullptr;
    }

    bool hasScript() const
    {
        return mScript != nullptr;
    }

    bool hasPhysics() const
    {
        return mPhysics != nullptr;
    }

private:
    sf::Sprite* mSprite;
    Script* mScript;
    Body* mPhysics;
};
}

#endif