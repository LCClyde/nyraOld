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
#include <nyra/PhysicsBody.h>

namespace nyra
{
//===========================================================================//
PhysicsBody::PhysicsBody(Type type,
           b2World& world)
{
    b2BodyDef bodyDef;
    if (type == DYNAMIC)
    {
        bodyDef.type = b2_dynamicBody;
    }
    mBody = world.CreateBody(&bodyDef);
}

//===========================================================================//
void PhysicsBody::addBox(const Vector2& size,
                         float density,
                         float friction)
{
    b2PolygonShape shape;
    b2FixtureDef fixture;
    shape.SetAsBox((size.x * Constants::METERS_PER_PIXEL) / 2.0,
                   (size.y * Constants::METERS_PER_PIXEL) / 2.0);
    fixture.density = density;
    fixture.friction = friction;
    fixture.shape = &shape;
    mBody->CreateFixture(&fixture);
}

//===========================================================================//
void PhysicsBody::addCircle(float radius,
                            float density,
                            float friction)
{
    b2FixtureDef fixture;
    b2CircleShape circle;
    circle.m_radius = radius * Constants::METERS_PER_PIXEL;
    fixture.density = density;
    fixture.friction = friction;
    fixture.shape = &circle;
    mBody->CreateFixture(&fixture);
}
}