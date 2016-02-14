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
#ifndef NYRA_CAMERA_H_
#define NYRA_CAMERA_H_

#include <nyra/Actor.h>
#include <SFML/Graphics.hpp>

namespace nyra
{
/*
 *  \class Camera
 *  \brief Classed used to setup automatic camera positioning.
 */
class Camera
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up an unitialized camera.
     */
    Camera();

    /*
     *  \func track
     *  \brief Sets the camera to track a target.
     *
     *  \param target The target to track.
     *  \param offset An offset to apply to the target
     *  \param speed The speed to lerp the camera. A value of 1.0
     *         results in a snapping camera. Lerp speed is currently
     *         not implemented.
     */
    void track(const Actor& target,
               const Vector2& offset,
               double lerpSpeed);

    /*
     *  \func update
     *  \brief Updates the camera position.
     *
     *  \param deltaTime The time that has passed since the last update
     *  \param view The view to apply changes to
     */
    void update(sf::RenderTarget& render);

    /*
     *  \func reset
     *  \brief Returns the camera to a default setting.
     */
    void reset();

private:
    const Actor* mTarget;
    Vector2 mOffset;

    // TODO: Implement a frame independent lerp.
    double mLerpSpeed;
};
}

#endif
