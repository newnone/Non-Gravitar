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
#ifndef NON_GRAVITAR_POLYLINEVIEW_HPP
#define NON_GRAVITAR_POLYLINEVIEW_HPP

#include "shape/Polyline.hpp"
#include "view/ShapeView.hpp"


namespace gvt {
	class PolylineView: public ShapeView {
		protected:
			static sf::Color const DEFAULT_COLOR;

			sf::Color mColor {DEFAULT_COLOR};
			sf::VertexArray mVertices;

			void updateView ();
			void updateDebugView() override;
			void updateRotation() override;
			void onDraw(
				shared_ptr<Shape> shape, RenderTarget &t, RenderStates s
			) const override;
		public:
			explicit PolylineView(shared_ptr<Polyline> shape);

			void setDebug (bool debug) override;
	};
}

#endif