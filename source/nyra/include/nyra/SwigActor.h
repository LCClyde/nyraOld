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
#ifndef NYRA_SWIG_ACTOR_H_
#define NYRA_SWIG_ACTOR_H_

#include <stddef.h>
#include <nyra/Actor.h>
#include <nyra/Vector2.h>

namespace nyra
{
/*
 *  \class SwigActor
 *  \brief The Python interface into an Actor object. Note that since this
 *         is a Python class it uses Python naming conventions.
 */
class SwigActor
{
public:
    /*
     *  \func Constructor
     *  \brief Nulls out the Actor data.
     */
    SwigActor();

    /*
     *  \func _set_position
     *  \brief Sets the position of the Actor
     *
     *  \param vector The desired position.
     */
    void _set_position(const Vector2& vector) const;

    /*
     *  \func _get_position
     *  \brief Gets the Actor's position. The component that is used to
     *         determine the position may vary.
     *
     *
     *  \return The Actor's position.
     */
    Vector2 _get_position() const;

    /*
     *  \func _get_velocity
     *  \brief Gets the Actor's velocity. This will give a warning if the
     *         object is not a physics object.
     *
     *  \return The Actor's linear velocity
     */
    Vector2 _get_velocity() const;

    /*
     *  \func _apply_force
     *  \brief Applies a force to an Actor. This will give a warning if the
     *         object is not a physics object
     *
     *  \param force The force to apply
     */
    void _apply_force(const Vector2& vector) const;

    /*
     *  \func _set_data
     *  \brief Sets the Actor data. This should be used internally only.
     *
     *  \param address The memory address of the Actor.
     */
    void _set_data(size_t address);

    /*
     *  \func _get_data
     *  \brief Gets the data pointer. This should be used internally only.
     *
     *  \return The memory address of the Actor.
     */
    size_t _get_data() const;

private:
    Actor* mData;
};
}

#endif
