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
#include <vector>
#include <utility>

#include "catch.hpp"
#include "utils/BoundingPolygon.hpp"

auto Triangle = &gvt::BoundingPolygon::triangle;
auto Rect = &gvt::BoundingPolygon::rectangle;
using namespace gvt;


TEST_CASE("BoundingPolygon::intersects()", "[BoundingPolygon]") {
	std::vector<BoundingPolygon> first = {
        // Do polygons clash with themselves?
		Triangle({0, 0}, {1, 1}, {0, 2}), Triangle({0, 0}, {1, 1}, {0, 2}),
		Rect({0, 2}, {2, 0}),

		// Testing more sophisticated cases
		Rect({0, 3}, {5, 0}), Rect({0, 4}, {9, 0}), Rect({0, 3}, {5, 0}),
		Rect({5, 7}, {13, 3}),

		// Testing objects which do not collide
        Rect({5, 10}, {10, 5}), Rect({5, 10}, {10, 5}),
	};
	std::vector<BoundingPolygon> second = {
		Triangle({0, 0}, {1, 1}, {0, 2}), Triangle({0, 0}, {1, 1}, {0, 2}),
		Rect({0, 2}, {2, 0}),

		Triangle({4, 2}, {5, 4}, {6, 2}), Triangle({2, 1}, {4, 3}, {6, 1}),
		Triangle({5, 2}, {6, 4}, {7, 2}), Triangle({7, 4}, {9, 6}, {11, 4}),

        Rect({11, 10}, {16, 5}), Triangle({12, 5}, {14, 10}, {16, 5})
	};
	std::vector<bool> expected {
	    true, true, true, true, true, true, true,
	    false, false
	};

	for (size_t i = 0; i < first.size(); i++) {
	    INFO("[" << i << "]");
		REQUIRE(first[i].intersects(second[i]) == expected[i]);
	}
}

TEST_CASE(
	"BoundingPolygon::intersects() w/ straight lines", "[BoundingPolygon]"
) {
	std::vector<BoundingPolygon> first = {
		// Does a line intersect with itself?
		{{-2, -2}, {2, 2}},
		// Do two crossed lines intersect?
		{{-2, -2}, {2, 2}},
		// Do two lines that only share a point intersect? (They should.)
		{{0, 0}, {2, 2}},
		// Do two parallel lines intersect?
		{{0, 0}, {2, 2}},
		// Do two almost-near lines intersect? (They should not.)
		{{0, 0}, {2, 2}},

		// Does a square intersect with its diagonal?
		{{-2, 2}, {2, 2}, {2, -2}, {-2, -2}},
		// Does a square intersect with one of its sides?
		{{-2, 2}, {2, 2}, {2, -2}, {-2, -2}},
		// Does a square intersect with a tangent line? (It should.)
		{{-2, 2}, {2, 2}, {2, -2}, {-2, -2}},
		// Does a square intersect with a line close to its tangent? (It
		// should not.)
		{{-2, 2}, {2, 2}, {2, -2}, {-2, -2}}
	};
	std::vector<BoundingPolygon> second = {
		{{-2, -2}, {2, 2}},
		{{2, 2}, {-2, -2}},
		{{2, 2}, {4, 0}},
		{{2, 0}, {4, 2}},
		{{2.05, 2}, {4.05, 0}},

		{{-2, -2}, {2, 2}},
		{{0, 2}, {2, 2}},
		{{0, 4}, {4, 0}},
		{{0, 4.1}, {4.1, 0}},
	};

	std::vector<bool> expected {
	    true, true, true, false, false,

	    true, true, true, false
	};

	for (size_t i = 0; i < first.size(); i++) {
	    INFO("[" << i << "]");
		REQUIRE(first[i].intersects(second[i]) == expected[i]);
	}
}

TEST_CASE(
	"AxialProjection::intersects()", "[BoundingPolygon][AxialProjection]"
) {
	std::pair<AxialProjection, AxialProjection> projections[] = {
		{{0, 1}, {2, 3}}, {{0, 2}, {1, 3}}, {{0, 3}, {1, 2}}, {{1, 3}, {0, 2}},
		{{0, 1}, {2, 3}}
	};
	bool expected[] = {false, true, true, true, false};
	size_t i = 0;

	for (auto pair: projections) {
		REQUIRE(pair.first.intersects(pair.second) == expected[i]);
		i++;
	}
}
