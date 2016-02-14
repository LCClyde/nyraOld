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
#ifndef NYRA_BODY_H_
#define NYRA_BODY_H_

#include <Box2D/Box2D.h>
#include <nyra/Vector2.h>
#include <nyra/Constants.h>
#include <vector>

namespace nyra
{
/*
 *  \class PhysicsBody
 *  \brief Represents a single phyiscs object that can be used on an Actor.
 *         This may have multiple shapes that make up the one body. All
 *         types of physics bodies (e.g. Static and Dynamic) are encapsulated
 *         by this class.
 */
class PhysicsBody
{
public:
    /*
     *  \enum Type
     *  \brief Used to determine how this physics object will interact
     *         with other Phyiscs objects.
     */
    enum Type
    {
        STATIC,
        DYNAMIC
    };

    /*
     *  \func Constructor
     *  \brief Creates a physics body.
     *
     *  \param type How does this physics body interact with other bodies.
     *  \param world The top level physics world.
     */
    PhysicsBody(Type type,
                b2World& world);

    /*
     *  \func addBox
     *  \brief Adds a solid box to the physics body.
     *
     *  \param size The size in pixels. This should be the whole width
     *         and height of the box.
     *  \param density The density of the object.
     *  \param friction The friction of the object.
     */
    void addBox(const Vector2& size,
                float density,
                float friction);

    /*
     *  \func getPosition
     *  \brief Obtains the position of the physics body.
     *
     *  \return The current position.
     */
    inline Vector2 getPosition() const
    {
        return Vector2(mBody->GetPosition()) * Constants::PIXELS_PER_METER;
    }

    /*
     *  \func setPosition
     *  \brief Sets the position of the physics body. Note that this ignores
     *         physics calculations.
     *
     *  \param position The desired position.
     */
    inline void setPosition(const Vector2& position)
    {
        mBody->SetTransform(
                (position * Constants::METERS_PER_PIXEL).toThirdParty<b2Vec2>(),
                mBody->GetAngle());
    }

    /*
     *  \func get
     *  \brief Returns the underlying native physics body.
     *
     *  \return The Box2D phyiscs object.
     */
    inline const b2Body& get() const
    {
        return *mBody;
    }

    /*
     *  \func get
     *  \brief Returns the underlying native physics body.
     *
     *  \return The Box2D phyiscs object.
     */
    inline b2Body& get()
    {
        return *mBody;
    }

private:
    b2Body* mBody;
};
}

#endif
