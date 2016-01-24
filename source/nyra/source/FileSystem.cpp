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
#include <nyra/FileSystem.h>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace nyra
{
//===========================================================================//
std::string readFile(const std::string& pathname)
{
    // Make sure the file exists
    if (!fileExists(pathname))
    {
        throw std::runtime_error("Unable to open file: " + pathname);
    }

    // Open the file
    std::ifstream file(pathname);

    // Seek to the end
    file.seekg(0, std::ios::end);
    const size_t size = file.tellg();

    // Create the string
    std::string buffer(size, ' ');
    file.seekg(0);

    // Read the file
    file.read(&buffer[0], size);
    return buffer;
}

//===========================================================================//
bool fileExists(const std::string& pathname)
{
    if (FILE* file = fopen(pathname.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}
}