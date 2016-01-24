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
#ifndef NYRA_JSON_NODE_H_
#define NYRA_JSON_NODE_H_

#include <string>
#include <vector>
#include <stdexcept>
#include <nyra/Vector2.h>
#include <rapidjson/document.h>

namespace nyra
{
class JSONNode
{
public:
    JSONNode(const rapidjson::Value* value = nullptr);

    std::string getString(const std::string& name) const;

    double getDouble(const std::string& name) const;

    JSONNode getNode(const std::string& name) const;

    Vector2 getVector2(const std::string& nodeName,
                       const std::string& x = "x",
                       const std::string& y = "y") const;

    template <typename T>
    std::vector<T> getArray(const std::string& name) const
    {
        hasValue(name, true);
        std::vector<T> ret;
        if ((*mValue)[name.c_str()].IsObject())
        {
            ret.push_back(T(JSONNode(&(*mValue)[name.c_str()])));
            return ret;
        }
        else if ((*mValue)[name.c_str()].IsArray())
        {
            const rapidjson::Value& array = (*mValue)[name.c_str()];
            for (rapidjson::SizeType ii = 0; ii < array.Size(); ++ii)
            {
                ret.push_back(T(JSONNode(&array[ii])));
            }
            return ret;
        }
        throw std::runtime_error(
                "Node: " + name + " does not contain a vector.");
    }

    bool hasValue(const std::string& name,
                  bool require = false) const;

private:
    const rapidjson::Value* const mValue;
};
}

#endif
