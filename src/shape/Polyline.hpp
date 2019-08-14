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
#ifndef NON_GRAVITAR_POLYLINE_HPP
#define NON_GRAVITAR_POLYLINE_HPP

#include <functional>
#include <iterator>
#include <list>
#include <memory>
#include <vector>
#include "Shape.hpp"
#include "ShapeVisitor.hpp"

template<typename T> using shared_ptr = std::shared_ptr<T>;


namespace gvt {
	/**
	 * A @c ShapeGenerator is a function returning part of a polyline shape,
	 * like a mountain, hill or any other subcomponent. This interface allows
	 * their construction to be modularized.
	 */
	using ShapeGenerator = std::function<std::vector<Vectord> ()>;

	/**
	 * Abstract @c Shape encapsulating primitives for point-to-point shapes.
	 * Note that vertices (points representing extremes of various lines)
	 * have their values encoded relative to the absolute position of this @c
	 * Polyline.
	 */
	class Polyline: public Shape {
		public:
			using iterator = std::vector<Vectord>::iterator;
		protected:
			// Polyline subclasses will often have a fixed number of vertices.
			// Employing a std::vector looks like a more reasonable choice
			// compared to std::list
			std::vector<Vectord> mVertices;

			/**
			 * @param vertices Vertices to initialize this polyline with. @c
			 * vertices will be emptied after this call.
			 */
			 // TODO How is C++ able to detect templates arguments without
			 //  them being specified?
			template<typename iterator>
			Polyline (Vectord position, iterator begin, iterator end):
					Shape(position), mVertices{begin, end} {
			}

			bool clashes (Shape2D const &other) const;
			bool clashes (Polyline const &other) const;
		public:

			inline size_t size() const;

			inline Vectord& operator[] (size_t index);
			inline const Vectord& operator[] (size_t index) const;

			inline iterator begin();
			inline iterator end();

			void accept (ShapeVisitor &v) override;
			/**
			 * Detects a collision again this object and @c other. If other
			 * is of type @c Shape2D, than the control is made against its
			 * own bounding polygon and all the lines comprising this polyline.
			 *
			 * @return @c true if @c *this clashes with @c other, @c false
			 * otherwise.
			 */
			bool clashes (Shape const &other) const override;
	};
}


namespace gvt {
	size_t Polyline::size() const {
		return mVertices.size();
	}

	Vectord &Polyline::operator[](size_t index) {
		return mVertices[index];
	}

	const Vectord &Polyline::operator[](size_t index) const {
		return mVertices[index];
	}

	Polyline::iterator Polyline::begin() {
		return mVertices.begin();
	}

	Polyline::iterator  Polyline::end() {
		return mVertices.end();
	}
}


#endif