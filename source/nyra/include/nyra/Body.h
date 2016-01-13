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
#ifndef NYRA_BODY_H_
#define NYRA_BODY_H_

#include <Box2D/Box2D.h>
#include <nyra/Vector2.h>
#include <vector>

namespace nyra
{
class Body
{
public:
    enum Type
    {
        STATIC,
        DYNAMIC
    };

    Body(Type type,
         double pixelsPerMeters,
         b2World& world);

    void addBox(const Vector2& size,
                float density,
                float friction);

    Vector2 getPosition() const
    {
        return Vector2(mBody->GetPosition()) * mPixelsPerMeters;
    }

    void setPosition(const Vector2& position)
    {
        mBody->SetTransform(
                (position * mMetersPerPixels).toThirdParty<b2Vec2>(),
                mBody->GetAngle());
    }

private:
    // TODO: We embed pixels to meters in here. Is there a better way to do
    //       this without copying the data everywhere? I want to avoid
    //       static in case I ever want multiple worlds. It might be safe
    //       to say that a game can only ever set this once for the entire
    //       game, but I am not sure yet.
    const double mPixelsPerMeters;
    const double mMetersPerPixels;
    b2Body* mBody;
};
}

#endif
