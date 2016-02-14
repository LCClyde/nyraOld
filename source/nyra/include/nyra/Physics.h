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
#ifndef NYRA_PHYSICS_H_
#define NYRA_PHYSICS_H_

#include <vector>
#include <memory>
#include <nyra/Vector2.h>
#include <Box2D/Box2D.h>
#include <nyra/PhysicsBody.h>
#include <nyra/PhysicsRenderer.h>

namespace nyra
{
/*
 *  \class Physics
 *  \brief Top level wrapper class for Box2D. This holds the world and manages
 *         physics bodies. This wrapper is updated on a step based timer
 *         and thus may update at a slightly different rate than the rest of
 *         the game.
 */
class Physics
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a Box2D based physics object.
     *
     *  \param gravity The gravity in meters per second squared. Note that
     *         (0, 0) is the top left meaning downward acceleration is
     *         in the positive y direction.
     *  \param renderer The physics renderer object used to draw collision
     *         objects to screen for debug purposes.
     */
    Physics(const Vector2& gravity,
            PhysicsRenderer& renderer);

    /*
     *  \func update
     *  \brief Update all physics. Note that this is not guarenteed to update
     *         anything if the game is running faster than the physics. The
     *         opposite can also occur. If the game is running slow, then the
     *         physics may update multiple times to catch up.
     *
     *  \param deltaTime The time since the last update in seconds.
     */
    void update(double deltaTime);

    /*
     *  \func reset
     *  \brief Returns the physics to a starting state.
     */
    void reset();

    /*
     *  \func addBody
     *  \brief Adds a new managed physics body to the phyisics system.
     *
     *  \param type The type of physics body to add.
     *  \return The managed phyiscs object.
     */
    PhysicsBody& addBody(PhysicsBody::Type type);

    /*
     *  \func render
     *  \brief Renders debug physics object to screen if they are enabled.
     */
    inline void render()
    {
        mWorld.DrawDebugData();
    }

private:
    b2World mWorld;
    std::vector<std::unique_ptr<PhysicsBody> > mBodies;
};
}

#endif
