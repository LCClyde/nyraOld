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
#ifndef NYRA_JSON_READER_H_
#define NYRA_JSON_READER_H_

#include <string>
#include <nyra/JSONNode.h>
#include <rapidjson/document.h>

namespace nyra
{
class JSONReader
{
public:
    JSONReader(const std::string& pathname);

    JSONNode getNode(const std::string& name) const
    {
        return mNode.getNode(name);
    }

    template <typename T>
    std::vector<T> getArray(const std::string& name) const
    {
        return mNode.getArray<T>(name);
    }

    bool hasValue(const std::string& name) const
    {
        return mNode.hasValue(name);
    }

private:
    rapidjson::Document mDocument;
    JSONNode mNode;
};
}

#endif
