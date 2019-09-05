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
#include "Shape.hpp"
#include "Rectangle.hpp"

using Shape = gvt::Shape;
using ShapeEvent = gvt::ShapeEvent;


Shape::Shape(Vectord position) : mPosition{position} {
}

void Shape::position(Vectord position) {
	if (position != mPosition) {
		mPosition = position;

		notify(std::make_shared<ShapeEvent>(ShapeEvent::Type::moved, this));
	}
}

void Shape::move(const Vectord &t) {
	mPosition += Vectord(t.x, t.y);

	notify(std::make_shared<ShapeEvent>(ShapeEvent::Type::moved, this));
}

void Shape::animate(float time) {
	if (mAccel.norm() != 0) {
		mVelocity += mAccel * time;
		move(mVelocity * time);
	}
}

void Shape::rotation(double r) {
	// TODO Shorten, if at all possible, this code that I have produced,
	//  which at first sight looks orribly bigger than it ought to be
	if (r >= 0)
		mRotation = r - (2.0 * M_PI) * floor(r / (2.0 * M_PI));
	else
		mRotation = r - (2.0 * M_PI) * ceil(r / (2.0 * M_PI));

	notify(std::make_shared<ShapeEvent>(ShapeEvent::Type::rotated, this));
}

void Shape::velocity(const Vectord &t) {
	mVelocity = t;
}

void Shape::collided(bool collided) {
	if (collided != mCollided) {
		mCollided = collided;

		notify(std::make_shared<ShapeEvent>(ShapeEvent::Type::collided, this));
	}
}


bool Shape::operator== (Shape const &o) const {
	return mPosition == o.mPosition && mVelocity == mVelocity &&
			mAccel == o .mAccel && mRotation == o.mRotation;
}

bool Shape::operator!= (Shape const &o) const {
	return !operator==(o);
}
