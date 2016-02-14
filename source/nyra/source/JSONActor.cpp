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
#include <nyra/JSONActor.h>
#include <nyra/JSONReader.h>

namespace nyra
{
//===========================================================================//
JSONActor::JSONActor(const std::string& pathname) :
    mReader(pathname),
    sprite(mReader.hasValue("sprite") ?
            new JSONSprite(mReader.getNode("sprite")) : nullptr),
    script(mReader.hasValue("script") ?
            new JSONScript(mReader.getNode("script")) : nullptr),
    physics(mReader.hasValue("physics") ?
            new JSONPhysics(mReader.getNode("physics")) : nullptr)
{
}

//===========================================================================//
JSONActor::JSONSprite::JSONSprite(const JSONNode& json) :
    filename(json.getString("filename")),
    origin(json.hasValue("origin") ?
            new Vector2(json.getVector2("origin")) : nullptr)
{
}

//===========================================================================//
JSONActor::JSONScript::JSONScript(const JSONNode& json) :
    module(json.getString("module")),
    className(json.getString("class")),
    update(json.hasValue("update") ?
            new std::string(json.getString("update")) : nullptr)
{
}

//===========================================================================//
JSONActor::JSONPhysics::JSONPhysics(const JSONNode& json) :
    type(json.getString("type")),
    shapes(json.getArray<JSONPhysicsShape>("shape"))
{
}

//===========================================================================//
JSONActor::JSONPhysics::JSONPhysicsShape::JSONPhysicsShape(
        const JSONNode& json) :
    type(json.getString("type")),
    size(json.getVector2("size", "width", "height")),
    friction(json.hasValue("friction") ?
            json.getDouble("friction") : 0.8),
    density(json.hasValue("density") ?
            json.getDouble("density") : 1.0)
{
}
}