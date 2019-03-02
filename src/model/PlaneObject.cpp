// MIT License
//
// Copyright (c) 2018 Oscar B. et al.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include "PlaneObject.hpp"
#include "Point.hpp"
#include "Rectangle.hpp"

using Event = gvt::Event;
using PlaneObject = gvt::PlaneObject;
using Point = gvt::Point;
using Trajectory = gvt::Trajectory;


const Event PlaneObject::MOVE;
const Event PlaneObject::ORIGIN;
const Event PlaneObject::ROTATION;
const Event PlaneObject::VELOCITY;


PlaneObject::PlaneObject(float x, float y): mX{x}, mY{y} {
}

Point PlaneObject::origin () const {
	return Point{mOriginX, mOriginY};
}

void PlaneObject::origin(float xcoord, float ycoord) {
	mOriginX = xcoord;
	mOriginY = ycoord;
	notify(ORIGIN);

	if (mPlane)
		mPlane->updateCollisions();
}

float PlaneObject::rotation() const {
	return mRotation;
}

void PlaneObject::rotation(unsigned r) {
	mRotation = r % 360;
	rotate();
	notify(ROTATION);

	if (mPlane)
		mPlane->updateCollisions();
}

void PlaneObject::velocity(Trajectory const &t) {
	mVelocity = t;
	notify(VELOCITY);
}

Trajectory PlaneObject::velocity() const {
	return mVelocity;
}

float PlaneObject::speed() const {
	return mVelocity.norm();
}

bool PlaneObject::clashes(gvt::PlaneObject const &o) const {
    return collisionBox().clashes(o.collisionBox());
}

void PlaneObject::move(float xcoord, float ycoord) {
    mX += xcoord;
    mY += ycoord;
	notify(MOVE);

    if (mPlane)
        mPlane->updateCollisions();
}

bool PlaneObject::operator== (PlaneObject const &o) const {
	return mX == o.mX && mY == o.mY && mOriginX == o.mOriginX &&
			mOriginY == o.mOriginY && mRotation == o.mRotation &&
			mVelocity == mVelocity && mPlane == o.mPlane;
}

bool PlaneObject::operator!= (PlaneObject const &o) const {
	return !operator==(o);
}