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
#include <nyra/Body.h>

namespace nyra
{
//===========================================================================//
Body::Body(Type type,
           double pixelsPerMeters,
           b2World& world) :
    mPixelsPerMeters(pixelsPerMeters),
    mMetersPerPixels(1.0 / pixelsPerMeters)
{
    b2BodyDef bodyDef;
    if (type == DYNAMIC)
    {
        bodyDef.type = b2_dynamicBody;
    }
    mBody = world.CreateBody(&bodyDef);
}

//===========================================================================//
void Body::addBox(const Vector2& size,
                  float density,
                  float friction)
{
    b2PolygonShape shape;
    b2FixtureDef fixture;
    shape.SetAsBox((size.x * mPixelsPerMeters) / 2.0,
                   (size.y * mPixelsPerMeters) / 2.0);
    fixture.density = density;
    fixture.friction = friction;
    fixture.shape = &shape;
    mBody->CreateFixture(&fixture);
}
}