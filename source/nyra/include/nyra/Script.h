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
#ifndef NYRA_SCRIPT_H_
#define NYRA_SCRIPT_H_

#include <string>
#include <unordered_map>
#include <nyra/AutoPy.h>

namespace nyra
{
/*
 *  \class Script
 *  \brief Creates a somewhat abstract Python object. This supports a single
 *         module and an optional class. All methods assigned will be from
 *         these. Methods are mapped to strings to allow them to be called
 *         generically.
 */
class Script
{
public:
   /*
    *  \func Constructor
    *  \brief Creates the Python script object.
    *
    *  \param moduleName The Python module
    *  \param className The Python class. If this does not have a class
    *         pass in an empty string. All methods will be assinged based
    *         on the module instead.
    *  \param data Because the Python layer is loaded through a shared
    *         object we need to pass in the data pointer so it has access
    *         to the memory.
    */
    Script(const std::string& moduleName,
           const std::string& className,
           void* data);

    /*
     *  \func addMethod
     *  \brief Registers a method to be called from C++.
     *
     *  \param methodKey The C++ key associated with the method
     *  \param methodName The name of the Python method
     */
    void addMethod(const std::string& methodKey,
                   const std::string& methodName);

    /*
     *  \func call
     *  \brief Calls a registered method
     *
     *  \param methodKey The name of the method to call.
     */
    inline void call(const std::string& methodKey)
    {
        if (!hasMethod(methodKey))
        {
            return;
        }

        callMethod(methodKey, getArgList());
    }

    /*
     *  \func call
     *  \brief Calls a registered method
     *
     *  \tparam T The type of the parameter.
     *  \param methodKey The name of the method to call.
     *  \param param A param to pass to python.
     */
    template <typename T>
    void call(const std::string& methodKey,
              T param)
    {
        if (!hasMethod(methodKey))
        {
            return;
        }

        callMethod(methodKey, getArgList<T>(param));
    }

private:
    inline bool hasMethod(const std::string& methodKey) const
    {
        return mMethods.find(methodKey) != mMethods.end();
    }

    void callMethod(const std::string& method,
                    const AutoPy& argList);

    AutoPy getArgList()
    {
        return AutoPy(PyTuple_New(0));
    }

    template <typename T>
    AutoPy getArgList(T param)
    {
        const AutoPy argList(PyTuple_New(1));
        addParam<T>(argList, 0, param);
        return argList;
    }

    template <typename T>
    void addParam(const AutoPy& argList,
                  size_t pos,
                  T value)
    {
        throw std::runtime_error("No specialziation available for param.");
    }

    AutoPy mModule;
    AutoPy mClass;
    AutoPy mInstance;
    std::unordered_map<std::string, AutoPy> mMethods;
};
}

#endif

