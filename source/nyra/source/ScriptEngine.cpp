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
#include <nyra/ScriptEngine.h>
#include <nyra/Logger.h>

namespace nyra
{
//===========================================================================//
ScriptEngine::ScriptEngine(void* engine)
{
    // Make sure Python is initialized first.
    if (!Py_IsInitialized())
    {
        Py_Initialize();
        Logger::info("Python initialized");
    }
    else
    {
        throw std::runtime_error("Python was reinitialized.");
    }

    mEngineScript.reset(new Script("nyra", "", engine));
}

//===========================================================================//
ScriptEngine::~ScriptEngine()
{
    // Kill all python and shut it down
    reset();
    mEngineScript.reset(nullptr);

    Py_Finalize();
}

//===========================================================================//
void ScriptEngine::callAll(const std::string& method)
{
    for (auto& script : mScripts)
    {
        script->call(method);
    }
}

//===========================================================================//
void ScriptEngine::reset()
{
    mScripts.clear();
}

//===========================================================================//
Script* ScriptEngine::addScript(const std::string& moduleName,
                                const std::string& className,
                                void* data)
{
    Script* script = new Script(moduleName, className, data);
    mScripts.push_back(std::unique_ptr<Script>(script));
    return script;
}
}