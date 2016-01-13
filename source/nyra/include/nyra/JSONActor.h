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
#include <rapidjson/document.h>
#include <nyra/Vector2.h>

namespace nyra
{
class JSONActor
{
public:
    JSONActor(const std::string& pathname);

    //=======================================================================//
    struct JSONSprite
    {
        JSONSprite(const rapidjson::Value& json);

        std::string filename;
    };

    //=======================================================================//
    struct JSONScript
    {
        JSONScript(const rapidjson::Value& json);

        std::string module;
        std::string className;

        std::unique_ptr<std::string> update;
    };

    //=======================================================================//
    struct JSONPhysics
    {
        JSONPhysics(const rapidjson::Value& json);

        std::string type;

        //====================================================================//
        struct JSONPhysicsShape
        {
            JSONPhysicsShape(const rapidjson::Value& json);

            std::string type;
            Vector2 size;
            float friction;
            float density;
        };

        std::vector<JSONPhysicsShape> shapes;
    };

    std::unique_ptr<JSONSprite> sprite;
    std::unique_ptr<JSONScript> script;
    std::unique_ptr<JSONPhysics> physics;
};
}

#endif
