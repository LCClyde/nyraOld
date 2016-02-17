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
#include <nyra/InputConstants.h>

namespace nyra
{
//===========================================================================//
Engine::Engine(const Config& config) :
    mConfig(config),
    mRenderPhysics(false),
    mElapsedTime(0.0),
    mTimePerFrame(1.0 / mConfig.framesPerSecond),
    mGraphics(mConfig.title,
              mConfig.windowPosition,
              mConfig.windowSize,
              mConfig.fullscreen,
              mConfig.vsync),
    mPhysicsRenderer(mGraphics.getWindow()),
    mPhysics(mConfig.gravity,
             mPhysicsRenderer),
    mScript(this)
{
    Logger::info("Engine initialized");
    mPhysicsRenderer.setRender(true);
    mInput.registerInput("render physics",
                         std::vector<size_t>(1, Keyboard::NUM_1));

    // Check for a default map
    if (!mConfig.defaultMap.empty())
    {
        loadMap(mConfig.defaultMap);
    }
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

    mScript.update(deltaTime);

    mPhysics.update(deltaTime);

    // Update dynamic actors
    for (auto actor : mDynamicActors)
    {
        actor->updateGraphicsWithPhysics();
    }

    // Update the camera
    mCamera.update(mGraphics.getWindow());

    // Check for physics rendering
    if (mConfig.debug && mInput.buttonPressed("render physics"))
    {
        mRenderPhysics = !mRenderPhysics;
        Logger::debug("Physics rendering now set to: " +
                ((mRenderPhysics) ? std::string("true") :
                                    std::string("false")));
    }

    // update the input
    mInput.update();

    mGraphics.render();

    // Check for physics rendering
    if (mConfig.debug && mRenderPhysics)
    {
        mPhysics.render();
    }
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
    const std::string pathname(mConfig.dataDir + "/maps/" + filename + ".json");
    Logger::info("Loading map: " + pathname);
    const JSONMap map(pathname);
    for (const auto& actor : map.actors)
    {
        Actor& created = addActor(actor.filename);
        created.setPosition(actor.position);
        //created.setRotation(actor.rotation);
    }

    // Tell all the actors everything is loaded
    mScript.init();
}

//===========================================================================//
void Engine::addGUI(const std::string& filename)
{
    const std::string pathname(mConfig.dataDir + "/gui/" + filename + ".json");
    GUI gui();
}

//===========================================================================//
Sprite& Engine::addSprite(const std::string& filename)
{
    const std::string pathname(mConfig.dataDir + "/textures/" + filename + ".png");
    return mGraphics.addSprite(pathname);
}

//===========================================================================//
Actor& Engine::addActor(const std::string& filename)
{
    // Parse JSON
    const std::string pathname(mConfig.dataDir + "/actors/" + filename + ".json");
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
        if (json.script->init.get())
        {
            script->addMethod("init", (*json.script->init));
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