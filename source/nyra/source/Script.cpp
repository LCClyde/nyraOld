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

    const AutoPy setDataList(PyTuple_New(1));
    PyTuple_SetItem(setDataList.get(), 0,
                    PyInt_FromSize_t(reinterpret_cast<size_t>(data)));
    PyObject_CallObject(mMethods["set_data"].get(), setDataList.get());
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
void Script::call(const std::string& methodKey)
{
    // Make sure this is not already assigned
    const auto& iter = mMethods.find(methodKey);
    if (iter == mMethods.end())
    {
        return;
    }

    const AutoPy argList(PyTuple_New(0));
    PyObject_CallObject(mMethods[methodKey].get(), argList.get());
}

}
