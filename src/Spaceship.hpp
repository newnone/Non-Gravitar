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
#ifndef NON_GRAVITAR_SPACESHIP_HPP
#define NON_GRAVITAR_SPACESHIP_HPP

#include "PlaneObject.hpp"
#include "PlaneTraits.hpp"


namespace gvt {
	class Spaceship: public PlaneObject, public WidthTrait, public HeightTrait
	{
		private:
			// Represents the current fuel amount in the ship
			size_t mFuel;
		protected:
			Rectangle collisionBox() const override;
		public:
			size_t fuel() const;
			/**
			 * @brief Recharges the current Spaceship instance by the fuel
			 * amount found in <b>fuel</b>.
			 * @param fuel Fuel instance.
			 */
			void recharge(Fuel &fuel);
			/**
			 * @brief Discharges the current Spaceship's fuel by <b>amount</b>,
			 * defaulted to 1.
			 */
			// TO-DO Verify that we can specify a default argument value, and
			// that Spaceship::discharge() can be specified even with no
			// arguments.
			void discharge(size_t amount = 1);
			/**
			 * @returns true if the current spaceship instance has still fuel
			 * in it, false othwerise.
			 */
			bool charged();

			bool operator== (PlaneObject const &o) const override;
	};
}


#endif
