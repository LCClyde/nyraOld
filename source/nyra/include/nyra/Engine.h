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
#include <nyra/Camera.h>
#include <nyra/Config.h>

namespace nyra
{
/*
 *  \class Engine
 *  \brief The top level class used to handle interactions between
 *         services. Creating more than one Engine is untested and should
 *         be avoided.
 */
class Engine
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an Engine object.
     *
     *  \param config A filled out config struct.
     */
    Engine(const Config& config);

    /*
     *  \func update
     *  \brief Moves the engine forward by one frame.
     *
     *  \return If this returns false then the engine has shutdown and should
     *          not be updated again.
     */
    bool update();

    /*
     *  \func loadMap
     *  \brief Loads a new map file into memory. Any previous information
     *         will be lost.
     *
     *  \param filename The name of the map file without an extension.
     *  \info Logs the name of the map file being loaded.
     */
    void loadMap(const std::string& filename);

    /*
     *  \func addActor
     *  \brief Creates a new managed actor.
     *
     *  \param filename The name of the actor file without an extension.
     */
    Actor& addActor(const std::string& filename);

    /*
     *  \func addGUI
     *  \brief Creates a new managed GUI.
     *
     *  \param filename The name of the GUI file without an extension.
     */
    void addGUI(const std::string& filename);

    /*
     *  \func getInput
     *  \brief Gets the top level input service.
     *
     *  \return The Input object.
     */
    inline Input& getInput()
    {
        return mInput;
    }

    /*
     *  \func getInput
     *  \brief Gets the top level input service.
     *
     *  \return The Input object.
     */
    inline const Input& getInput() const
    {
        return mInput;
    }

    /*
     *  \func getLogger
     *  \brief Returns the registered logger. This should only be used
     *         by the scripting layer. This is needed because it is loaded
     *         as a shared object and does not share the memory space as
     *         the main application. Internal code should use the static
     *         methods available in the Logger class.
     *
     *  \return The Logger object.
     */
    Logger& getLogger() const
    {
        return Logger::getRegisteredLogger();
    }

    /*
     *  \func getCamera
     *  \brief Gets the camera instance.
     *
     *  \return The camera instance.
     */
    Camera& getCamera()
    {
        return mCamera;
    }

private:
    void reset();

    bool tick(double deltaTime);

    Sprite& addSprite(const std::string& filename);

    Config mConfig;
    bool mRenderPhysics;

    sf::Clock mTimer;
    double mElapsedTime;
    const double mTimePerFrame;
    Input mInput;

    // Graphics
    Graphics mGraphics;

    // Physics
    PhysicsRenderer mPhysicsRenderer;
    Physics mPhysics;

    // Script
    ScriptEngine mScript;

    Camera mCamera;

    // Containers
    std::vector<std::unique_ptr<Actor> > mActors;
    std::map<int32_t, tgui::Gui> mGui;

    std::vector<Actor*> mDynamicActors;
};
}

#endif
