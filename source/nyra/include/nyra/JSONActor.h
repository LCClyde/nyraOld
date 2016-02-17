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
#ifndef NYRA_JSON_ACTOR_H_
#define NYRA_JSON_ACTOR_H_

#include <string>
#include <memory>
#include <vector>
#include <nyra/JSONNode.h>
#include <nyra/JSONReader.h>
#include <nyra/Vector2.h>

namespace nyra
{
/*
 *  \func JSONActor
 *  \brief Parses Actor values out of a JSON file.
 */
struct JSONActor
{
public:
    /*
     *  \func Constructor
     *  \brief Parses an Actor JSON file.
     *
     *  \param pathname The pathname to the JSON file.
     */
    JSONActor(const std::string& pathname);

    /*
     *  \class JSONSprite
     *  \brief Parses a JSON Actor Sprite.
     */
    struct JSONSprite
    {
        /*
         *  \func Constructor
         *  \brief Parses a JSON Sprite from a json node.
         *
         *  \param json The node to parse from.
         */
        JSONSprite(const JSONNode& json);

        /*
         *  \var filename
         *  \brief The filename without extension of the sprite image.
         */
        const std::string filename;

        /*
         *  \var origin
         *  \brief An optional origin point represented in pixels.
         */
        const std::unique_ptr<const Vector2> origin;
    };

    /*
     *  \class JSONScript
     *  \brief Parses a JSON Script from a json node.
     */
    struct JSONScript
    {
        /*
         *  \func Constructor
         *  \brief Parses a JSON Script from a json node.
         *
         *  \param json The node to parse from.
         */
        JSONScript(const JSONNode& json);

        /*
         *  \var module
         *  \brief The name of the Python module
         */
        const std::string module;

        /*
         *  \var className
         *  \brief The name of the class.
         */
        const std::string className;

        /*
         *  \var update
         *  \brief An optional update function name.
         */
        const std::unique_ptr<const std::string> update;

        /*
         *  \var init
         *  \brief An optional init funciton name.
         */
        const std::unique_ptr<const std::string> init;
    };

    /*
     *  \class JSONPhysics
     *  \brief Parses a JSON Physics object from a json node.
     */
    struct JSONPhysics
    {
        /*
         *  \func Constructor
         *  \brief Parse a JSON Physics object from a json node.
         *
         *  \param json The node to parse from
         */
        JSONPhysics(const JSONNode& json);

        /*
         *  \var type
         *  \brief The type of physics body (static, dynamic, etc)
         */
        const std::string type;

        /*
         *  \class JSONPhysicsShape
         *  \brief Parses a physic shape from a json node.
         */
        struct JSONPhysicsShape
        {
            /*
             *  \func Constructor
             *  \brief Parses a physics shape from a json node.
             *
             *  \param json The node to parse from
             */
            JSONPhysicsShape(const JSONNode& json);

            /*
             *  \var type
             *  \brief Describes the type of shape (circle, box, line, etc)
             */
            const std::string type;

            /*
             *  \var size
             *  \brief The size of the shape. Only relevant to some shapes.
             */
            const Vector2 size;

            /*
             *  \var friction
             *  \brief The friction for this shape
             */
            const double friction;

            /*
             *  \var density
             *  \brief The density for this shape.
             */
            const double density;

            /*
             *  \var radius
             *  \brief The radius of a circle collision
             */
            const double radius;
        };

        /*
         *  \var shapes
         *  \brief A list of shapes associated with this physics object.
         */
        const std::vector<JSONPhysicsShape> shapes;
    };

private:
    const JSONReader mReader;

public:
    /*
     *  \var sprite
     *  \brief An optional sprite for this Actor
     */
    const std::unique_ptr<const JSONSprite> sprite;

    /*
     *  \var script
     *  \brief An optional script for this Actor
     */
    const std::unique_ptr<const JSONScript> script;

    /*
     *  \var physics
     *  \brief An optional physics object for this Actor.
     */
    const std::unique_ptr<const JSONPhysics> physics;
};
}

#endif
