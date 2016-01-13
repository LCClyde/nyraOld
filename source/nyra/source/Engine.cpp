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
#include <nyra/Engine.h>
#include <nyra/JSONActor.h>

namespace nyra
{
//===========================================================================//
Engine::Engine(const std::string& dataDir,
               const std::string& title,
               const Vector2& position,
               const Vector2& size,
               bool fullscreen,
               bool vsync,
               const Vector2& gravity,
               double physicsTicksPerSecond,
               double pixelsPerMeters) :
    mDataDir(dataDir),
    mEngineScript("nyra", "", this),
    mGraphics(title,
              position,
              size,
              fullscreen,
              vsync),
    mPhysics(gravity,
             physicsTicksPerSecond,
             pixelsPerMeters)
{
}

//===========================================================================//
bool Engine::update()
{
    const double deltaTime = mTimer.restart().asSeconds();

    if (!mGraphics.clear())
    {
        return false;
    }

    // Call script updates
    for (auto& script : mScripts)
    {
        script->call("update");
    }

    mPhysics.update(deltaTime);

    // Update dynamic actors
    for (auto actor : mDynamicActors)
    {
        actor->updateGraphicsWithPhysics();
    }

    mGraphics.render();

    // update the input
    mInput.update();

    mGraphics.present();

    return true;
}

//===========================================================================//
void Engine::addGUI(const std::string& filename)
{
    GUI gui(mDataDir + "/gui/" + filename + ".json");
}

//===========================================================================//
sf::Sprite& Engine::addSprite(const std::string& filename)
{
    return mGraphics.addSprite(
            mDataDir + "/textures/" + filename + ".png").get();
}

//===========================================================================//
Actor& Engine::addActor(const std::string& filename)
{
    // Parse JSON
    JSONActor json(mDataDir + "/actors/" + filename + ".json");

    mActors.push_back(Actor());
    Actor& actor = mActors.back();

    // Check for a sprite
    if (json.sprite.get())
    {
        sf::Sprite& sprite = addSprite(json.sprite->filename);
        actor.setSprite(sprite);
    }

    // Check for a script
    if (json.script.get())
    {
        Script* script = new Script(
                json.script->module,
                json.script->className,
                &actor);
        mScripts.push_back(std::unique_ptr<Script>(script));

        if (json.script->update.get())
        {
            script->addMethod("update", (*json.script->update));
        }
        actor.setScript(*script);
    }

    // Check for phyics
    if (json.physics.get())
    {
        Body::Type type;
        if (json.physics->type == "dynamic")
        {
            type = Body::DYNAMIC;
        }
        else if (json.physics->type == "static")
        {
            type = Body::STATIC;
        }
        else
        {
            throw std::runtime_error(
                    "Invalid physics type: " + json.physics->type);
        }

        mBodies.push_back(mPhysics.addBody(type));
        Body& body = mBodies.back();

        for (const auto& shape : json.physics->shapes)
        {
            if (shape.type == "box")
            {
                body.addBox(shape.size,
                            shape.density,
                            shape.friction);
            }
            else
            {
                throw std::runtime_error(
                        "Invalid physics shape: " + shape.type);
            }
        }
        actor.setPhysics(body);

        // Check if this is a dynamic renderable object
        if (json.physics->type != "static" && actor.hasSprite())
        {
            mDynamicActors.push_back(&actor);
        }
    }
    return mActors.back();
}

}