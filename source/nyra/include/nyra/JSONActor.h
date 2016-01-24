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
struct JSONActor
{
public:
    JSONActor(const std::string& pathname);

    //=======================================================================//
    struct JSONSprite
    {
        JSONSprite(const JSONNode& json);

        const std::string filename;
        const std::unique_ptr<const Vector2> origin;
    };

    //=======================================================================//
    struct JSONScript
    {
        JSONScript(const JSONNode& json);

        const std::string module;
        const std::string className;

        const std::unique_ptr<const std::string> update;
    };

    //=======================================================================//
    struct JSONPhysics
    {
        JSONPhysics(const JSONNode& json);

        const std::string type;

        //====================================================================//
        struct JSONPhysicsShape
        {
            JSONPhysicsShape(const JSONNode& json);

            const std::string type;
            const Vector2 size;
            const double friction;
            const double density;
        };

        const std::vector<JSONPhysicsShape> shapes;
    };

private:
    const JSONReader mReader;

public:
    const std::unique_ptr<const JSONSprite> sprite;
    const std::unique_ptr<const JSONScript> script;
    const std::unique_ptr<const JSONPhysics> physics;
};
}

#endif
