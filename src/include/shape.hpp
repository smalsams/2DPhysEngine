#pragma once
#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <cmath>

#include "manifold.hpp"
#include "rectangle_capsule.hpp"

namespace seng {
	class circle;
	class polygon;
	class rectangle;
	class body_shape {
	public:
		virtual ~body_shape() = default;

		/*
		 * @brief Enum to represent the type of shape
		 */
		enum shape_type
		{
			CIRCLE,
			POLYGON,
			RECTANGLE
		};

		/*
		 * @brief Get the type of shape
		 * @return shape_type
		 */
		[[nodiscard]] virtual shape_type get_type() const = 0;
		/*
		 * @brief Get the rectangle capsule of the shape, used for broad phase collision detection
		 * @return rectangle_capsule
		 */
		virtual rectangle_capsule get_rectangle_capsule() = 0;
		/*
		 * @brief Get the size of the rectangle capsule
		 * @return vector2<float>
		 */
		virtual vector2<float> get_rectangle_capsule_size() = 0;
		/*
		 * @brief calculate the collision between this shape and another shape, calls the appropriate collision function based on the type of shape
		 * @param other: the other shape
		 * @param this_transform: the transform of this shape
		 * @param other_transform: the transform of the other shape
		 * @see transform, body_shape, circle, polygon, rectangle
		 * @see circle_collision, polygon_collision, rectangle_collision
		 * @return manifold
		 */
		[[nodiscard]] manifold collision(const body_shape& other, const transform& this_transform, const transform& other_transform) const;

		vector2<float> center{};
	protected:
		[[nodiscard]] virtual manifold handle_collision(const circle& other, const transform& this_transform, const transform& other_transform) const = 0;
		[[nodiscard]] virtual manifold handle_collision(const polygon& other, const transform& this_transform, const transform& other_transform) const = 0;
		[[nodiscard]] virtual manifold handle_collision(const rectangle& other, const transform& this_transform, const transform& other_transform) const = 0;
	};

}
#endif