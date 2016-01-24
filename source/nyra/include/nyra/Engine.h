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
#ifndef NYRA_ENGINE_H_
#define NYRA_ENGINE_H_

#include <string>
#include <map>
#include <memory>
#include <stdint.h>
#include <nyra/Vector2.h>
#include <nyra/GUI.h>
#include <nyra/Sprite.h>
#include <nyra/Actor.h>
#include <nyra/Constants.h>
#include <nyra/ScriptEngine.h>
#include <nyra/Input.h>
#include <nyra/Graphics.h>
#include <nyra/Physics.h>
#include <nyra/Logger.h>
#include <nyra/PhysicsRenderer.h>

namespace nyra
{
class Engine
{
public:
    Engine(const std::string& dataDir = Constants::APP_PATH + "../data/",
           const std::string& title = "Nyra Engine",
           const Vector2& position = Vector2(0, 0),
           const Vector2& size = Vector2(1920, 1080),
           bool fullscreen = false,
           bool vsync = false,
           const Vector2& gravity = Vector2(0, 10.0),
           double physicsTicksPerSecond = 30.0);

    bool update();

    void loadMap(const std::string& filename);

    Actor& addActor(const std::string& filename);

    void addGUI(const std::string& filename);

    Input& getInput()
    {
        return mInput;
    }

    const Input& getInput() const
    {
        return mInput;
    }

    Logger& getLogger() const
    {
        return Logger::getRegisteredLogger();
    }

private:
    void reset();

    sf::Sprite& addSprite(const std::string& filename);

    const std::string mDataDir;

    sf::Clock mTimer;
    Input mInput;


    // Graphics
    Graphics mGraphics;

    // Physics
    PhysicsRenderer mPhysicsRenderer;
    Physics mPhysics;

    // Script
    ScriptEngine mScript;

    // Containers
    std::vector<std::unique_ptr<Actor> > mActors;
    std::map<int32_t, tgui::Gui> mGui;

    std::vector<Actor*> mDynamicActors;
};
}

#endif
