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
#ifndef NYRA_JSON_CONFIG_H_
#define NYRA_JSON_CONFIG_H_

#include <string>
#include <nyra/JSONReader.h>
#include <nyra/Config.h>

namespace nyra
{
class JSONConfig
{
public:
    /*
     *  \func Constructor
     *  \brief Reads and stores a config file.
     *
     *  \param pathname The pathname to the config.json file.
     */
    JSONConfig(const std::string& pathname);

    /*
     *  \func get
     *  \brief Gets the underlying config object.
     *
     *  \return The filled out config object
     */
    const Config& get() const
    {
        return mConfig;
    }

private:
    const JSONReader mReader;
    Config mConfig;
};
}

#endif
