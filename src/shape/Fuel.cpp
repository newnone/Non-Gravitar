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
#include "Fuel.hpp"
#include "Rectangle.hpp"
#include "bounding-polygon/BoundingRectangle.hpp"

using namespace gvt;


Fuel::Fuel(Vectord position, unsigned fuel): Shape(position) {
	mFuel = fuel;
}

unsigned Fuel::fuel() const {
	return mFuel;
}

void Fuel::empty() {
	mFuel = 0;
}

void Fuel::accept(ShapeVisitor &visitor) {
	visitor.visitFuel(*this);
}

double Fuel::width() const {
	return Fuel::WIDTH;
}

double Fuel::height() const {
	return Fuel::HEIGHT;
}

BoundingPolygon Fuel::collisionPolygon() const {
	BoundingRectangle r = {
		mPosition, mPosition + Vectord{WIDTH, HEIGHT}
	};
	r.rotate(mRotation);

	return r;
}

bool Fuel::operator== (Shape const &o) const {
	auto *other = dynamic_cast<Fuel const *>(&o);

	if (other)
		return Shape::operator==(*other) && mFuel == other->mFuel;

	return false;
}

