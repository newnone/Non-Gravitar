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
#ifndef NON_GRAVITAR_RANDOM_HPP
#define NON_GRAVITAR_RANDOM_HPP

#include <algorithm>
#include <random>


namespace gvt {
	template<typename N>
	class UniRandom {
		private:
            std::uniform_int_distribution<N> mDist;
			std::default_random_engine mEngine;
		public:
			inline UniRandom(N low, N high);
			inline N operator()();
	};

	template<>
	class UniRandom<float> {
		private:
			std::uniform_real_distribution<float> mDist;
			std::default_random_engine mEngine;
		public:
			inline UniRandom(float low, float high);
			inline float operator()();
	};

	template<>
	class UniRandom<double> {
		private:
            std::uniform_real_distribution<double> mDist;
			std::default_random_engine mEngine;
		public:
			inline UniRandom(double low, double high);
			inline double operator()();
	};


	template<typename I> class IteratorRandomizer {
		private:
			I mBegin;
			UniRandom<int> mChoice;
		public:
			inline IteratorRandomizer (I begin, I end);
			inline I operator() ();
	};
}


#include "Random.tpp"


#endif