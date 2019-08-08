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
#ifndef NON_GRAVITAR_SHAPE_HPP
#define NON_GRAVITAR_SHAPE_HPP

#include <ostream>
#include <bounding-polygon/BoundingPolygon.hpp>
#include "utils/Event.hpp"
#include "utils/Vector.hpp"


namespace gvt {
	class Rectangle;
	class ShapeVisitor;

	/**
	 * @brief An abstract base class for subsequent shape objects. Note that
	 * coordinates are taken by default from the <i>top left</i> corner, hence
	 * not an arbitrary center (which may vary from shape to shape).
	 * @see gvt::Plane
	 */
	class Shape: public GVTEventDispatcher {
		protected:
			// mPosition encodes coordinates of the top-left corner, not of an
			// arbitrary center
            Vectorf mPosition, mVelocity{0, 0}, mAccel{0, 0};
			float mRotation{0};

			bool mDestroyed{false};

			Shape() = default;
			explicit Shape(Vectorf position);
		public:
			using ostream = std::ostream;

			virtual ~Shape();

			/**
			 * @return The position vector associated to this @c Shape.
			 */
			inline Vectorf position() const;
			/**
			 * @param position Position vector to set for this @c Shape.
			 */
			void position(Vectorf position);
			/**
			 * @brief Move the current object along the given trajectory.
			 * @param t Trajectory to follow
			 */
			void move(Vectorf const &t);
			/**
			 * Moves the object along the trajectory described by the @c
			 * Shape velocity, which in turn is updated by the @c Shape
			 * acceleration by the given amount of time.
			 * @param time Velocity factor, in seconds.
			 */
			void animate(float time);

			/**
			 * @return The angle with respect to the object origin of the
			 * current @c Shape instance, given in radians.
			 */
			inline float rotation() const;
			/**
			 * @param r The rotation angle to set for this object, in radians
			 * @todo Test the implementation
			 */
			void rotation(float r);
			/**
			 * @param r Amount of radians to add to the current rotation value
			 */
			inline void rotate(float r);

			inline bool destroyed() const;
			inline void destroyed(bool state);

			/**
			 * Sets the velocity of this @c Shape. Note that the unit measure
			 * utilized is point/sec.
			 * @param t Velocity value to set to the current @c Shape instance.
			 */
			void velocity(Vectorf const &t);
			/**
			 * @return The velocity vector associated with the current
			 * @c Shape.
			 */
			Vectorf velocity() const;
			/**
			 * @return The current @c Shape speed, as a scalar value.
			 */
			float speed() const;
			/**
			 * @param a Acceleration vector to set for this @c Shape.
			 */
			void acceleration(Vectorf const &a);
			/**
			 * @return The acceleration vector associated to this @c Shape.
			 */
			Vectorf acceleration() const;

			/**
			 * Lets a @c ShapeVisitor perform its operation on the 
			 * implementing subclass.
			 * 
			 * @see ShapeVisitor
			 */
			virtual void accept(ShapeVisitor &visitor) = 0;

			/**
			 * @return A @c Rectangle object representing the bounds used to
			 * detect collisions with another @c Shape. The coordinates
			 * accounted for are <i>global</i>, that is are measured against
			 * the global coordinate system.
			 */
			virtual BoundingPolygon collisionPolygon() const = 0;
			/**
			 * @return @c true if the boundaries of the current @c Shape clash
			 * with those of the object @c o.
			 */
			bool clashes(Shape const &o) const;
			/**
			 * @return @c true if the object at the current position meets the
			 * other @c Shape given as argument by following the trajectory @c
			 * t
			 */
			bool meets(Shape const &o, Vectorf const &t) const;

			virtual bool operator== (Shape const &o) const;
			virtual bool operator!= (Shape const &o) const;
	};

	struct ShapeEvent: public Event {
		enum class Type {
			unspecified = 0, moved, rotated, destroyed
		};

		ShapeEvent::Type type{ShapeEvent::Type::unspecified};
		Shape *shape{nullptr};

		inline ShapeEvent();
		inline ShapeEvent(ShapeEvent::Type type, Shape *shape);
	};
}


// Definitions of constructs to be kept in the local translation-unit.
// The `i' in `.ipp' stands for "implementation".
#include "Shape.ipp"


#endif
