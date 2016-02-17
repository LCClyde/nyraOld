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
#include <nyra/JSONNode.h>
#include <stdexcept>
#include <vector>

namespace nyra
{
//===========================================================================//
JSONNode::JSONNode(const rapidjson::Value* value) :
    mValue(value)
{
}

//===========================================================================//
JSONNode::~JSONNode()
{
}

//===========================================================================//
JSONNode JSONNode::getNode(const std::string& name) const
{
    hasValue(name, true);
    if (!(*mValue)[name.c_str()].IsObject())
    {
        throw std::runtime_error(
                "Node: " + name + " does not contain an object.");
    }
    return JSONNode(&(*mValue)[name.c_str()]);
}

//===========================================================================//
bool JSONNode::getBool(const std::string& name) const
{
    hasValue(name, true);
    if (!(*mValue)[name.c_str()].IsBool())
    {
        throw std::runtime_error(
            "Node: " + name + " does not contain a bool.");
    }
    return (*mValue)[name.c_str()].GetBool();
}

//===========================================================================//
std::string JSONNode::getString(const std::string& name) const
{
    hasValue(name, true);
    if (!(*mValue)[name.c_str()].IsString())
    {
        throw std::runtime_error(
                "Node: " + name + " does not contain a string.");
    }
    return (*mValue)[name.c_str()].GetString();
}

//===========================================================================//
double JSONNode::getDouble(const std::string& name) const
{
    hasValue(name, true);
    if (!(*mValue)[name.c_str()].IsDouble())
    {
        throw std::runtime_error(
                "Node: " + name + " does not contain a double.");
    }
    return (*mValue)[name.c_str()].GetDouble();
}

//===========================================================================//
Vector2 JSONNode::getVector2(const std::string& nodeName,
                             const std::string& x,
                             const std::string& y) const
{
    JSONNode node = getNode(nodeName);
    return Vector2(node.getDouble(x), node.getDouble(y));
}

//===========================================================================//
bool JSONNode::hasValue(const std::string& name,
                        bool require) const
{
    if (!mValue)
    {
        throw std::runtime_error(
                "Attempting to obtain an invalid JSON node.");
    }

    if (!mValue->HasMember(name.c_str()))
    {
        if (require)
        {
            throw std::runtime_error(
                "Required node: " + name + " does not exist.");
        }
        return false;
    }
    return true;
}
}