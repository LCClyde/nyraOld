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
#ifndef NYRA_SCRIPT_ENGINE_H_
#define NYRA_SCRIPT_ENGINE_H_

#include <nyra/Script.h>
#include <vector>
#include <string>
#include <memory>

namespace nyra
{
/*
 *  \class ScriptEngine
 *  \brief Provides a top level class for wrapping the global Python calls.
 *         This function does allocate and dealloc global objects. Creating
 *         more than one of this class would be undefined behavior.
 */
class ScriptEngine
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up Python.
     *
     *  \param engine Python needs access to the engine pointer because it
     *         is in a different memory space than the rest of the engine.
     */
    ScriptEngine(void* engine);

    /*
     *  \func Destructor
     *  \brief This will shutdown the Python script layer completely.
     */
    ~ScriptEngine();

    /*
     *  \func reset
     *  \brief Resets the scripting layer to a starting position.
     */
    void reset();

    /*
     *  \func update
     *  \brief Calls update on all the scripts.
     */
    inline void update()
    {
        callAll("update");
    }

    /*
     *  \func init
     *  \brief Calls the init method on all scripts
     */
    void init()
    {
        callAll("init");
    }

    /*
     *  \func addScript
     *  \brief Adds a new managed script.
     *
     *  \param moduleName The name of the module
     *  \param className The name of the class. If this is a module only
     *         script, you can pass in an empty string here.
     *  \param data Any script defined data. For actors this should point
     *         to the underlying C++ Actor object.
     */
    Script* addScript(const std::string& moduleName,
                      const std::string& className,
                      void* data);

private:
    void callAll(const std::string& methodName);

    std::unique_ptr<Script> mEngineScript;
    std::vector<std::unique_ptr<Script> > mScripts;
};
}

#endif