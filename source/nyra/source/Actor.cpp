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
#include <nyra/Actor.h>
#include <nyra/Logger.h>

namespace nyra
{
//===========================================================================//
Actor::Actor() :
    mSprite(nullptr),
    mScript(nullptr),
    mPhysics(nullptr)
{
}

//===========================================================================//
void Actor::setPosition(const Vector2& position) const
{
    bool foundComponent = false;
    if (mSprite)
    {
        mSprite->get().setPosition(position.toThirdParty<sf::Vector2f>());
        foundComponent = true;
    }
    if (mPhysics)
    {
        mPhysics->setPosition(position);
        foundComponent = true;
    }

    if (!foundComponent)
    {
        Logger::warn("Actor has no positional components.");
    }
}

//===========================================================================//
Vector2 Actor::getPosition() const
{
    if (mSprite)
    {
        return mSprite->get().getPosition();
    }
    else if (mPhysics)
    {
        return mPhysics->getPosition();
    }

    Logger::warn("Actor has no positional components.");
    return Vector2();
}

//===========================================================================//
Vector2 Actor::getVelocity() const
{
    if (mPhysics)
    {
        return mPhysics->get().GetLinearVelocity();
    }
    Logger::warn("Actor has no physics component for velocity.");
    return Vector2();
}

//===========================================================================//
void Actor::applyImpulse(const Vector2& impulse) const
{
    if (!mPhysics)
    {
        Logger::warn("Actor has no phyiscs component to apply impulse to");
        return;
    }

    mPhysics->get().ApplyLinearImpulse(
            impulse.toThirdParty<b2Vec2>(),
            mPhysics->get().GetWorldCenter(),
            true);
}

//===========================================================================//
void Actor::applyForce(const Vector2& impulse) const
{
    if (!mPhysics)
    {
        Logger::warn("Actor has no phyiscs component to apply force to");
        return;
    }

    mPhysics->get().ApplyForce(
            impulse.toThirdParty<b2Vec2>(),
            mPhysics->get().GetWorldCenter(),
            true);
}

//===========================================================================//
void Actor::updateGraphicsWithPhysics() const
{
    if (!mSprite || !mPhysics)
    {
        Logger::warn("Attempting to update graphics with physics on an "
                     "Actor with the proper components.");
        return;
    }
    mSprite->get().setPosition(
            mPhysics->getPosition().toThirdParty<sf::Vector2f>());
    mSprite->get().setRotation(mPhysics->getRotation());
}
}