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
#include <nyra/Physics.h>
#include <iostream>

namespace
{
//===========================================================================//
static const size_t VELOCITY_ITERATIONS = 8;
static const size_t POSITION_ITERATIONS = 3;
}

namespace nyra
{
//===========================================================================//
Physics::Physics(const Vector2& gravity,
                 double ticksPerSecond,
                 double pixelsPerMeters) :
    mElapsedTime(0.0),
    mPixelsPerMeters(pixelsPerMeters),
    mFrameTime(1.0 / ticksPerSecond),
    mWorld((gravity).toThirdParty<b2Vec2>())
{
}

//===========================================================================//
void Physics::update(double deltaTime)
{
    mElapsedTime += deltaTime;
    while (mElapsedTime > mFrameTime)
    {
        mWorld.Step(mFrameTime,
                    VELOCITY_ITERATIONS,
                    POSITION_ITERATIONS);
        mElapsedTime -= mFrameTime;
    }
}

//===========================================================================//
Body Physics::addBody(Body::Type type)
{
    Body body(type, mPixelsPerMeters, mWorld);
    return body;
}
}