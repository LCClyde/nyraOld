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
#include <nyra/FileSystem.h>

namespace
{
static std::string err;
}

namespace nyra
{
//===========================================================================//
JSONActor::JSONActor(const std::string& pathname)
{
    err = pathname;

    rapidjson::Document document;
    document.Parse(readFile(pathname).c_str());

    if (document.HasMember("sprite"))
    {
        sprite.reset(new JSONSprite(document["sprite"]));
    }

    if (document.HasMember("script"))
    {
        script.reset(new JSONScript(document["script"]));
    }

    if (document.HasMember("physics"))
    {
        physics.reset(new JSONPhysics(document["physics"]));
    }
}

//===========================================================================//
JSONActor::JSONSprite::JSONSprite(const rapidjson::Value& json)
{
    if (!json.HasMember("filename") || !json["filename"].IsString())
    {
        throw std::runtime_error(
                "Invalid sprite filename (filename:string) for: " + err);
    }
    filename = json["filename"].GetString();
}

//===========================================================================//
JSONActor::JSONScript::JSONScript(const rapidjson::Value& json)
{
    if (!json.HasMember("module") || !json["module"].IsString())
    {
        throw std::runtime_error(
                "Invalid script module (module:string) for: " + err);
    }

    if (!json.HasMember("class") || !json["class"].IsString())
    {
        throw std::runtime_error(
                "Invalid script class (class:string) for: " + err);
    }

    module = json["module"].GetString();
    className = json["class"].GetString();

    if (json.HasMember("update"))
    {
        if (!json["update"].IsString())
        {
            throw std::runtime_error(
                    "Invalid script update (update:string) for: " + err);
        }
        update.reset(new std::string(json["update"].GetString()));
    }
}

//===========================================================================//
JSONActor::JSONPhysics::JSONPhysics(const rapidjson::Value& json)
{
    if (!json.HasMember("type") || !json["type"].IsString())
    {
        throw std::runtime_error(
                "Invalid physics type (type:string) for: " + err);
    }
    type = json["type"].GetString();

    // Check if there is only one body
    if (!json.HasMember("shape"))
    {
        throw std::runtime_error(
                "Invalid physics shape (shape:object|array) for: " + err);
    }

    if (json["shape"].IsObject())
    {
        shapes.push_back(JSONPhysicsShape(json["shape"]));
    }
    else if (json["shape"].IsArray())
    {
        throw std::runtime_error(
                "Physics shape Arrays are currently not supported: " + err);
    }
    else
    {
        throw std::runtime_error(
                "Invalid physics shape (shape:object|array) for: " + err);
    }
}

//===========================================================================//
JSONActor::JSONPhysics::JSONPhysicsShape::JSONPhysicsShape(
        const rapidjson::Value& json)
{
    // Check for type
    if (!json.HasMember("type") || !json["type"].IsString())
    {
        throw std::runtime_error(
                "Invalid physics shape type (type:string) for: " + err);
    }
    type = json["type"].GetString();

    if (json.HasMember("width") && json.HasMember("height"))
    {
        if (!json["width"].IsDouble() || !json["height"].IsDouble())
        {
            throw std::runtime_error("Invalid physics shape width/height "
                    "(width|double height|double) for: " + err);
        }

        size.x = json["width"].GetDouble();
        size.y = json["height"].GetDouble();
    }
    else
    {
        throw std::runtime_error("Only width/height size is currently "
                "avaliable for physics objects: " + err);
    }

    // Check for density
    if (json.HasMember("density"))
    {
        if (!json["density"].IsDouble())
        {
            throw std::runtime_error("Invalid physics shape density "
                    "(density|double) for: " + err);
        }
        density = json["density"].GetDouble();
    }
    else
    {
        density = 1.0;
    }

    // Check for friction
    if (json.HasMember("friction"))
    {
        if (!json["friction"].IsDouble())
        {
            throw std::runtime_error("Invalid physics shape friction "
                    "(friction|double) for: " + err);
        }
        friction = json["friction"].GetDouble();
    }
    else
    {
        friction = 1.0;
    }
}
}