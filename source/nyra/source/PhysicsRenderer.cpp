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

#include <nyra/PhysicsRenderer.h>
#include <SFML/System.hpp>
#include <nyra/Constants.h>
#include <nyra/Logger.h>
#include <iostream>

namespace
{
//===========================================================================//
sf::Color toColor(const b2Color& color, sf::Uint8 alpha)
{
    return sf::Color(static_cast<sf::Uint8>(color.r * 255),
                     static_cast<sf::Uint8>(color.g * 255),
                     static_cast<sf::Uint8>(color.b * 255),
                     alpha);
}

//===========================================================================//
sf::Vector2f toVector(const b2Vec2& point)
{
    return sf::Vector2f(point.x * nyra::Constants::PIXELS_PER_METER,
                        point.y * nyra::Constants::PIXELS_PER_METER);
}
}

namespace nyra
{
//===========================================================================//
PhysicsRenderer::PhysicsRenderer(sf::RenderWindow& window) :
    mWindow(window)
{
}

//===========================================================================//
void PhysicsRenderer::DrawTransform(const b2Transform& transform)
{
    // TODO: Implement
    /*const float lineProportion = 0.15;
    const b2Vec2& point1 = transform.p;

    //red (X axis)
    b2Vec2 point2 = point1 + (lineProportion * transform.R.col1);
    const sf::Shape redLine = sf::Shape::Line(
            point1.x * Constants::METERS_TO_PIXELS,
            point1.y * Constants::METERS_TO_PIXELS,
            point2.x * Constants::METERS_TO_PIXELS,
            point2.y * Constants::METERS_TO_PIXELS,
            1, sf::Color::Red);

    //green (Y axis)
    point2 = point1 - (lineProportion * transform.R.col2);
    const sf::Shape greenLine = sf::Shape::Line(
            point1.x * Constants::METERS_TO_PIXELS,
            point1.y * Constants::METERS_TO_PIXELS,
            point2.x * Constants::METERS_TO_PIXELS,
            point2.y * Constants::METERS_TO_PIXELS,
            1, sf::Color::Green);

    mWindow.Draw(redLine);
    mWindow.Draw(greenLine);*/
}

//===========================================================================//
void PhysicsRenderer::DrawSegment(const b2Vec2& point1,
                                  const b2Vec2& point2,
                                  const b2Color& color)
{
    const sf::Vertex line[] =
    {
        sf::Vertex(toVector(point1), toColor(color, 255)),
        sf::Vertex(toVector(point2), toColor(color, 255))
    };
    mWindow.draw(line, 2, sf::Lines);
}

//===========================================================================//
void PhysicsRenderer::DrawSolidCircle(const b2Vec2& center,
                                      float32 radius,
                                      const b2Vec2& axis,
                                      const b2Color& color)
{
    sf::CircleShape circle(radius * Constants::PIXELS_PER_METER);
    circle.setFillColor(toColor(color, 128));
    circle.setPosition(toVector(center));

    // TODO: Add axis
    mWindow.draw(circle);
}

//===========================================================================//
void PhysicsRenderer::DrawCircle(const b2Vec2& center,
                                 float32 radius,
                                 const b2Color& color)
{
    sf::CircleShape circle(radius * Constants::PIXELS_PER_METER);
    circle.setFillColor(toColor(color, 0));
    circle.setOutlineColor(toColor(color, 255));
    circle.setOutlineThickness(1.0);
    circle.setPosition(toVector(center));
    mWindow.draw(circle);
}

//===========================================================================//
void PhysicsRenderer::DrawSolidPolygon(const b2Vec2* vertices,
                                       int32 vertexCount,
                                       const b2Color& color)
{
    sf::ConvexShape convex;
    convex.setPointCount(vertexCount);
    std::vector<sf::Vertex> verts;
    for (int32 ii = 0; ii < vertexCount; ++ii)
    {
        convex.setPoint(ii, toVector(vertices[ii]));
    }
    convex.setFillColor(toColor(color, 128));
    convex.setOutlineColor(toColor(color, 255));
    convex.setOutlineThickness(1.0);
    mWindow.draw(convex);
}

//===========================================================================//
void PhysicsRenderer::DrawPolygon(const b2Vec2* vertices,
                                  int32 vertexCount,
                                  const b2Color& color)
{
    sf::ConvexShape convex;
    convex.setPointCount(vertexCount);
    std::vector<sf::Vertex> verts;
    for (int32 ii = 0; ii < vertexCount; ++ii)
    {
        convex.setPoint(ii, toVector(vertices[ii]));
    }
    convex.setFillColor(toColor(color, 0));
    convex.setOutlineThickness(1.0);
    convex.setOutlineColor(toColor(color, 255));
    mWindow.draw(convex);
}
}
