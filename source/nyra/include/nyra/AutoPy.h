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
#ifndef NYRA_AUTO_PY
#define NYRA_AUTO_PY

#include <Python.h>

namespace nyra
{
/*
 *  \class AutoPy
 *  \brief A wrapper class around a PyObject that allows it to be used
 *         similar to an std::unique_ptr. It offers copy and move
 *         semantics.
 */
class AutoPy
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an AutoPy from a PyObject.
     *
     *  \param object The PyObject to be managed.
     */
    AutoPy(PyObject* object = nullptr);

    /*
     *  \func Constructor
     *  \brief Copy constructs an AutoPy from another AutoPy.
     *
     *  \param other The AutoPy to copy from.
     */
    AutoPy(const AutoPy& other);

    /*
     *  \func Constructor
     *  \brief Moves an AutoPy from one source to another. This steals the
     *         PyObject.
     *
     *  \param other The AutoPy to move from.
     */
    AutoPy(AutoPy&& other);

    /*
     *  \func Assignment
     *  \brief Assigns an AutoPy from another AutoPy object.
     *
     *  \param other The AutoPy to assign from.
     *  \return The copied AutoPy object.
     */
    AutoPy& operator=(const AutoPy& other);

    /*
     *  \func Assignment
     *  \brief Assign an AutoPy from rvalue. This steals the PyObject.
     *
     *  \param other The AutoPy to move.
     *  \return The AutoPy object with the managed PyObject.
     */
    AutoPy& operator=(AutoPy&& other);

    /*
     *  \func Destructor
     *  \brief Decrements the PyObject if it exists.
     */
    ~AutoPy();

    /*
     *  \func reset
     *  \brief Updates the underlying PyObject. This will decrement the
     *         current PyObject and it will no longer be managed here.
     *
     *  \param object The new PyObject to be managed. It is valid to pass
     *         in nullptr.
     */
    void reset(PyObject* object);

    /*
     *  \func get
     *  \brief Returns the underlying PyObject. It is not recommended that
     *         you do anything to adjust the reference count manually.
     *
     *  \return The managed PyObject.
     */
    PyObject* get() const
    {
        return mObject;
    }

private:
    void release();

    PyObject* mObject;
};
}

#endif
