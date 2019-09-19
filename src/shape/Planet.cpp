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
#include "Planet.hpp"


namespace gvt {
	Planet::Planet (Vectord position, double radius):
			Shape2D(position), mRadius{radius}, mPolygon{8} {
		// Planet, in its most basic form, is shown as an octagon. To achieve
		// that form we need 8 vertices
		double factor = M_PI / 4.0;

		for (unsigned vertex = 0; vertex < 8; vertex++)
			mPolygon[vertex] = radius * Vectord(factor * vertex);
	}

	void Planet::surface(shared_ptr<PlanetSurface> s) {
		mSurface = std::move(s);
	}

	shared_ptr<PlanetSurface> Planet::surface() {
		return mSurface;
	}

	BoundingPolygon Planet::collisionPolygon() const {
		mPolygon.position(mPosition);
		mPolygon.rotate(mRotation, rotationCenter());

		return mPolygon;
	}

	void Planet::accept (ShapeVisitor &visitor) {
		visitor.visitPlanet(*this);
	}

	bool Planet::operator== (Shape const &o) const {
        auto other = dynamic_cast<Planet const *>(&o);

        if (other)
        	return Shape2D::operator==(o);

        return false;
	}
}

