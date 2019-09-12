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
#ifndef NON_GRAVITAR_SOLAR_SYSTEM_HPP
#define NON_GRAVITAR_SOLAR_SYSTEM_HPP

#include <memory>
#include "shape/Planet.hpp"
#include "CollisionGroup.hpp"


namespace gvt {
	class SolarSystem: public CollisionGroup {
		private:
			double mWidth, mHeight;

			/**
			 * Updates height and width values upon insertion of a new @c Shape.
			 */
			void onInsertShape (shared_ptr<Shape> shape) override;
		public:
			static std::shared_ptr<SolarSystem> makeRandom (
				unsigned planets, double minRadius, double maxRadius,
				Vectord minPos, Vectord maxPos
			);

			inline double height() const;
			inline double width() const;
	};
}


namespace gvt {
	double SolarSystem::height() const {
		return mHeight;
	}

	double SolarSystem::width() const {
		return mWidth;
	}
}


#endif