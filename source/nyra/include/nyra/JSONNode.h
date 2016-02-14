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
/*
 *  \class JSONNode
 *  \brief A wrapper class around rapidjson::Value that can be used to
 *         quickly extract values from a node. This uses individual methods
 *         for each get method rather than templates because it less verbose
 *         from a user standpoint that way (templates will require writing
 *         the template parameter anyways).
 */
class JSONNode
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a JSONNode object.
     *
     *  \param value The underlying rapidjson object this node represents.
     */
    JSONNode(const rapidjson::Value* value = nullptr);

    /*
     *  \func Destructor
     *  \brief There is no functionality here. It is provided to allow
     *         proper inheritance.
     */
    ~JSONNode();

    /*
     *  \func getString
     *  \brief Extract a string from a node
     *
     *  \param name The name of the string
     *  \return The value of the string
     *  \throw If the string does not exist.
     */
    std::string getString(const std::string& name) const;

    /*
     *  \func getDouble
     *  \brief Extract a double from a node
     *
     *  \param name The name of the double
     *  \return The value of the double
     *  \throw If the double does not exist
     */
    double getDouble(const std::string& name) const;

    /*
     *  \func getNode
     *  \brief Extract a node from another node.
     *
     *  \param name The name of the node
     *  \return The new json node.
     *  \throw If the node does not exists
     */
    JSONNode getNode(const std::string& name) const;

    /*
     *  \func getVector2
     *  \brief Extract a nyra::Vector2 from a node. A Vector2 is a seperate
     *         JSON object with two parameters for x and y.
     *
     *  \param nodeName The name of the node that holds the Vector.
     *  \param x An optional override for the name of the x string
     *  \param y An optional override for the name of the y string
     *  \return The value of the Vector2
     *  \throw If the Vector2 does not exist.
     */
    Vector2 getVector2(const std::string& nodeName,
                       const std::string& x = "x",
                       const std::string& y = "y") const;

    /*
     *  \func getArray
     *  \brief Extract a vector of some type of JSON object. This requires
     *         a class that takes a single JSONNode for a constructor.
     *         This also supports extracting a single object, in which case
     *         a vector of length 1 is created.
     *
     *  \tparam T The element type of the vector. It must support construction
     *          from a single JSONNode.
     *  \param name The name of the array.
     *  \return The value of the array.
     *  \throw If the array does not exist as either a JSON array or a JSON
     *         object.
     */
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

    /*
     *  \func hasValue
     *  \brief Check if a node has a value.
     *
     *  \param name The name of the node to check.
     *  \param require Is it an error to not have this value? In general
     *         this is internal only. The get* methods already check
     *         this internally, thus you can just call them and allow
     *         them to throw instead.
     *  \return True if the value is in the node
     *  \throw If the value is not found and require is true.
     */
    bool hasValue(const std::string& name,
                  bool require = false) const;

private:
    const rapidjson::Value* const mValue;
};
}

#endif
