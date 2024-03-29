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
/*
 *  \class JSONReader
 *  \brief Provides a top level wrapper to rapidjson::Document. This also
 *         functions as a complete JSONNode to make interacting with it
 *         transparent as you go down the nodes.
 */
class JSONReader : public JSONNode
{
public:
    /*
     *  \func Constructor
     *  \brief Loads and parses a JSON file.
     *
     *  \param pathname The complete pathname to the json file.
     */
    JSONReader(const std::string& pathname);

private:
    rapidjson::Document mDocument;
};
}

#endif
