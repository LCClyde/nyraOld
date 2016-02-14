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
#include <nyra/Logger.h>
#include <nyra/JSONMap.h>

namespace nyra
{
//===========================================================================//
Engine::Engine(const std::string& dataDir,
               double framesPerSecond,
               const std::string& title,
               const Vector2& position,
               const Vector2& size,
               bool fullscreen,
               bool vsync,
               const Vector2& gravity) :
    mDataDir(dataDir),
    mTimePerFrame(1.0 / framesPerSecond),
    mElapsedTime(0.0),
    mGraphics(title,
              position,
              size,
              fullscreen,
              vsync),
    mPhysicsRenderer(mGraphics.getWindow()),
    mPhysics(gravity,
             mPhysicsRenderer),
    mScript(this)
{
    Logger::info("Engine initialized");
    mPhysicsRenderer.setRender(true);
}

//===========================================================================//
bool Engine::update()
{
    const double deltaTime = mTimer.restart().asSeconds();

    if (mGraphics.getVsyncFlag())
    {
        return tick(deltaTime);
    }
    else
    {
        mElapsedTime += deltaTime;
        if (mElapsedTime >= mTimePerFrame)
        {
            if (!tick(mTimePerFrame))
            {
                return false;
            }
            mElapsedTime -= mTimePerFrame;
        }
        if (mElapsedTime >= mTimePerFrame)
        {
            const size_t skippedFrames =
                    static_cast<size_t>(mElapsedTime / mTimePerFrame);
            Logger::warn("FPS is too high, skipping " +
                         std::to_string(skippedFrames) + " frames.");
            mElapsedTime -= mTimePerFrame * skippedFrames;
        }
    }

    return true;
}

//===========================================================================//
bool Engine::tick(double deltaTime)
{
    if (!mGraphics.clear())
    {
        return false;
    }

    mScript.update();

    mPhysics.update(deltaTime);

    // Update dynamic actors
    for (auto actor : mDynamicActors)
    {
        actor->updateGraphicsWithPhysics();
    }

    // Update the camera
    mCamera.update(mGraphics.getWindow());

    // update the input
    mInput.update();

    mGraphics.render();
    mPhysics.render();
    mGraphics.present();

    return true;
}

//===========================================================================//
void Engine::reset()
{
    mScript.reset();
    mPhysics.reset();
    mGraphics.reset();
    mDynamicActors.clear();
    mActors.clear();
    mCamera.reset();
}

//===========================================================================//
void Engine::loadMap(const std::string& filename)
{
    reset();
    const std::string pathname(mDataDir + "/maps/" + filename + ".json");
    Logger::info("Loading map: " + pathname);
    const JSONMap map(pathname);
    for (const auto& actor : map.actors)
    {
        Actor& created = addActor(actor.filename);
        created.setPosition(actor.position);
        //created.setRotation(actor.rotation);
    }
}

//===========================================================================//
void Engine::addGUI(const std::string& filename)
{
    const std::string pathname(mDataDir + "/gui/" + filename + ".json");
    GUI gui();
}

//===========================================================================//
Sprite& Engine::addSprite(const std::string& filename)
{
    const std::string pathname(mDataDir + "/textures/" + filename + ".png");
    return mGraphics.addSprite(pathname);
}

//===========================================================================//
Actor& Engine::addActor(const std::string& filename)
{
    // Parse JSON
    const std::string pathname(mDataDir + "/actors/" + filename + ".json");
    JSONActor json(pathname);

    mActors.push_back(std::unique_ptr<Actor>(new Actor()));
    Actor& actor = *mActors.back();

    // Check for a sprite
    if (json.sprite.get())
    {
        Sprite& sprite = addSprite(json.sprite->filename);

        if (json.sprite->origin.get())
        {
            sprite.get().setOrigin(
                    json.sprite->origin->toThirdParty<sf::Vector2f>());
        }
        else
        {
            sprite.get().setOrigin(sf::Vector2f(
                    (sprite.get().getTexture()->getSize().x / 2.0f),
                    (sprite.get().getTexture()->getSize().y / 2.0f)));
        }
        actor.setSprite(sprite);
    }

    // Check for a script
    if (json.script.get())
    {
        Script* script = mScript.addScript(
                json.script->module,
                json.script->className,
                &actor);

        if (json.script->update.get())
        {
            script->addMethod("update", (*json.script->update));
        }
        actor.setScript(*script);
    }

    // Check for phyics
    if (json.physics.get())
    {
        PhysicsBody::Type type;
        if (json.physics->type == "dynamic")
        {
            type = PhysicsBody::DYNAMIC;
        }
        else if (json.physics->type == "static")
        {
            type = PhysicsBody::STATIC;
        }
        else
        {
            throw std::runtime_error(
                    "Invalid physics type: " + json.physics->type);
        }

        PhysicsBody& body = mPhysics.addBody(type);

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
    return *mActors.back();
}

}