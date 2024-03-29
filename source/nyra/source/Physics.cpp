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
#include <nyra/Logger.h>

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
                 PhysicsRenderer& renderer) :
    mWorld((gravity).toThirdParty<b2Vec2>())
{
    Logger::info("Physics initialized");
    mWorld.SetDebugDraw(&renderer);
}

//===========================================================================//
void Physics::update(double deltaTime)
{
    mWorld.Step(deltaTime,
                VELOCITY_ITERATIONS,
                POSITION_ITERATIONS);
}

//===========================================================================//
void Physics::reset()
{
    for (auto& body : mBodies)
    {
        mWorld.DestroyBody(&body->get());
    }
    mBodies.clear();
}

//===========================================================================//
PhysicsBody& Physics::addBody(PhysicsBody::Type type)
{
    PhysicsBody* body = new PhysicsBody(type, mWorld);
    mBodies.push_back(std::unique_ptr<PhysicsBody>(body));
    return *body;
}
}