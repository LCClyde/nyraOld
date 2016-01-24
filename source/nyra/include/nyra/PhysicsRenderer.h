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
#ifndef NYRA_PHYSICS_RENDERER_H_
#define NYRA_PHYSICS_RENDERER_H_

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace nyra
{
class PhysicsRenderer : public b2Draw
{
public:
    PhysicsRenderer(sf::RenderWindow& window);

    void DrawPolygon(const b2Vec2* vertices,
                     int32 vertexCount,
                     const b2Color& color);

    void DrawSolidPolygon(const b2Vec2* vertices,
                          int32 vertexCount,
                          const b2Color& color);

    void DrawCircle(const b2Vec2& center,
                    float32 radius,
                    const b2Color& color);

    void DrawSolidCircle(const b2Vec2& center,
                         float32 radius,
                         const b2Vec2& axis,
                         const b2Color& color);

    void DrawSegment(const b2Vec2& point1,
                     const b2Vec2& point2,
                     const b2Color& color);

    void DrawTransform(const b2Transform& transform);

    void setRender(bool value)
    {
        SetFlags(b2Draw::e_shapeBit);
    }

private:
    sf::RenderWindow& mWindow;
};
}

#endif
