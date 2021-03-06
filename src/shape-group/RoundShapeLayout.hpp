// MIT License
//
// Copyright (c) 2018 Oscar B.
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
#ifndef NON_GRAVITAR_ROUND_SHAPE_LAYOUT_HPP
#define NON_GRAVITAR_ROUND_SHAPE_LAYOUT_HPP

#include "ShapeLayout.hpp"


namespace gvt {
	/**
	 * A shape layout capable of arranging its shapes around a circumference.
	 * This layout has a predetermined number of cells, exceeding which
	 * causes an exception to be thrown.
	 */
	class RoundShapeLayout: public ShapeLayout {
		private:
			Vectord mCenter;
			double mRadius, mFactor;
			unsigned mShapesNum;
		public:
			RoundShapeLayout (Vectord center, double radius, unsigned shapesNum);

			inline Vectord center() const;
			Vectord operator() (shared_ptr<Shape>, unsigned) override;
	};
}


namespace gvt {
	Vectord RoundShapeLayout::center() const {
		return mCenter;
	}
}


#endif