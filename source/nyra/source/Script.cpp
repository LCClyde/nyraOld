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
#include <nyra/Script.h>
#include <nyra/Logger.h>
#include <iostream>
#include <frameobject.h>

namespace nyra
{
//===========================================================================//
Script::Script(const std::string& moduleName,
               const std::string& className,
               void* data)
{
    const AutoPy pyModuleName(PyString_FromString(moduleName.c_str()));
    if (!pyModuleName.get())
    {
        throw std::runtime_error(
                "Unable to create Python string: " + moduleName);
    }
    mModule.reset(PyImport_Import(pyModuleName.get()));
    if (!mModule.get())
    {
        throw std::runtime_error("Unable to open Python module: " + moduleName);
    }

    if (!className.empty())
    {
        mClass.reset(PyObject_GetAttrString(mModule.get(), className.c_str()));
        if (!mClass.get())
        {
            throw std::runtime_error(
                    "Unable to open class module: " + className);
        }

        AutoPy argList(PyTuple_New(0));
        mInstance.reset(PyObject_CallObject(mClass.get(), argList.get()));
        if (!mInstance.get())
        {
            throw std::runtime_error("Unable to create instace of: " +
                    moduleName + "::" + className);
        }
    }

    // Call the set_data method by default to initialize the instance.
    addMethod("set_data", "_set_data");
    call<size_t>("set_data", reinterpret_cast<size_t>(data));
}

//===========================================================================//
void Script::addMethod(const std::string& methodKey,
                       const std::string& methodName)
{
    // Make sure this is not already assigned
    const auto& iter = mMethods.find(methodKey);
    if (iter != mMethods.end())
    {
        throw std::runtime_error("Unable to add method: " +
                methodKey + " the method already exists.");
    }

    mMethods[methodKey] = PyObject_GetAttrString(
            mInstance.get() ? mInstance.get() : mModule.get(),
            methodName.c_str());
    if (!mMethods[methodKey].get())
    {
        throw std::runtime_error("Unable to find method: " + methodName);
    }
}

//===========================================================================//
void Script::callMethod(const std::string& method,
                        const AutoPy& argList)
{
    PyObject_CallObject(mMethods[method].get(), argList.get());

    // Check for error
    PyObject* error = PyErr_Occurred();
    if (error)
    {
        // Fetch the error
        PyObject* type;
        PyObject* value;
        PyObject* traceback;
        PyErr_Fetch(&type, &value, &traceback);

        // Get the error message
        const std::string errorString  = PyString_AsString(value);

        // Try to get the full traceback
        PyThreadState* state = PyThreadState_GET();
        if (state && state->frame)
        {
            PyFrameObject* frame = state->frame;
            while (frame)
            {
                const std::string frameString =
                        std::string(PyString_AsString(
                                frame->f_code->co_filename)) +
                        "(" + std::to_string(frame->f_lineno) + "): " +
                        PyString_AsString(frame->f_code->co_name);
                Logger::error(frameString);
                frame = frame->f_back;
            }
        }
        throw std::runtime_error(errorString);
    }
}

//===========================================================================//
template <>
void Script::addParam(const AutoPy& argList,
                      size_t pos,
                      double value)
{
    PyTuple_SetItem(argList.get(), pos,
                    PyFloat_FromDouble(value));
}

//===========================================================================//
template <>
void Script::addParam(const AutoPy& argList,
                      size_t pos,
                      size_t value)
{
    PyTuple_SetItem(argList.get(), pos,
                    PyInt_FromSize_t(value));
}

}
