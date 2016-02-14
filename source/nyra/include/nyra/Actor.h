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
#ifndef NYRA_ACTOR_H_
#define NYRA_ACTOR_H_

#include <string>
#include <nyra/Sprite.h>
#include <nyra/Vector2.h>
#include <nyra/Script.h>
#include <nyra/PhysicsBody.h>

namespace nyra
{
/*
 *  \class Actor
 *  \brief Provides a common interface for a component based entity system.
 *         Individual components can be added an maintained here.
 *         This never owns memory. It is used to manage how components fit
 *         together.
 */
class Actor
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the internal structure of the Actor class. All components
     *         will start in a NULL state.
     */
    Actor();

    /*
     *  \func setSprite
     *  \brief Sets the Actor sprite object. This should be used internally
     *         only.
     *
     *  \param sprite The sprite that will be associated with this Actor.
     */
    inline void setSprite(Sprite& sprite)
    {
        mSprite = &sprite;
    }

    /*
     *  \func setScript
     *  \brief Sets the Actor script object. This should be used internally
     *         only.
     *
     *  \param script The script that will be associated with the Actor.
     */
    inline void setScript(Script& script)
    {
        mScript = &script;
    }

    /*
     *  \func setPhysics
     *  \brief Sets the Actor physics body object. This should be used
     *         internally only.
     *
     *  \param physics The physics body that will associated with the Actor.
     */
    inline void setPhysics(PhysicsBody& physics)
    {
        mPhysics = &physics;
    }

    /*
     *  \func setPosition
     *  \brief Sets the position of the Actor. This will determine what
     *         needs to be set based on available components.
     *
     *  \param position The desired position.
     *  \warn Warns if there are no components accept the position.
     */
    void setPosition(const Vector2& position) const;

    /*
     *  \func getPosition
     *  \brief Gets the position of the Actor. This will go from most to least
     *         likely components to try to find a position.
     *
     *  \return The Actor position
     *  \warn Warns if no components contain positional information.
     */
    Vector2 getPosition() const;

    /*
     *  \func getVelocity
     *  \brief Gets the linear velocity of the actor in meters per second
     *
     *  \return The velocity.
     *  \warn Warns if no physics components are available.
     */
    Vector2 getVelocity() const;

    /*
     *  \func applyImpulse
     *  \brief Applies an impulse to the actor.
     *
     *  \param impulse The size of the impulse in meters per second.
     *  \warn Warns if no components contain physics information.
     */
    void applyImpulse(const Vector2& impulse) const;

    /*
     *  \func applyForce
     *  \brief Applies a force to the actor
     *
     *  \param force The force to apply
     *  \warn Warns if no components contain physics information.
     */
    void applyForce(const Vector2& force) const;

    /*
     *  \func getVelocity
     *  \brief Gets the linear velocity of the Actor.
     *
     *  \return The Actor's velocity
     *  \warn Warns if there is no physics component.
     */

    /*
     *  \func updateGraphicsWithPhysics
     *  \brief If the physics updates the its transform, then the sprites needs
     *         to also update its transform. This call transfers that
     *         information. This should only be called internally.
     *
     *  \warn Warns if there is not a physics or sprite component.
     */
    void updateGraphicsWithPhysics() const;

    /*
     *  \func hasSprite
     *  \brief Checks if the Actor has a Sprite Component
     *
     *  \return True if there is a Sprite Component
     */
    bool hasSprite() const
    {
        return mSprite != nullptr;
    }

    /*
     *  \func hasScript
     *  \brief Checks if the Actor has a Script Component
     *
     *  \return True if there is a Script Component
     */
    bool hasScript() const
    {
        return mScript != nullptr;
    }

    /*
     *  \func hasPhysics
     *  \brief Checks if the Actor has a Physics Component
     *
     *  \return True if there is a Physics Component
     */
    bool hasPhysics() const
    {
        return mPhysics != nullptr;
    }

private:
    Sprite* mSprite;
    Script* mScript;
    PhysicsBody* mPhysics;
};
}

#endif