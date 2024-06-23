#pragma once

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <vector>

#include "shape.hpp"

namespace seng
{
	class rectangle final : public body_shape
	{
	public:
		explicit rectangle(const vector2<float>& sizes) : half_extents_(sizes / 2)
		{
			top_left_ = -half_extents_;
			bottom_right_ = half_extents_;
		}
		/*
		 * @copydoc body_shape::get_type
		 */
		[[nodiscard]] shape_type get_type() const override;

		/*
		 * @brief makes a polygon out of the rectangle (4 points)
		 */
		[[nodiscard]] polygon to_polygon() const;
		/*
		 * @copydoc body_shape::get_rectangle_capsule
		 */
		rectangle_capsule get_rectangle_capsule() override;

		[[nodiscard]] manifold handle_collision(const circle& other, const transform& this_transform,
		                                        const transform& other_transform) const override;
		[[nodiscard]] manifold handle_collision(const polygon& other, const transform& this_transform,
		                                         const transform& other_transform) const override;
		[[nodiscard]] manifold handle_collision(const rectangle& other, const transform& this_transform,
		                                           const transform& other_transform) const override;

		vector2<float> get_rectangle_capsule_size() override;
		/*
		 * @brief Get the half extents of the rectangle (width/2, height/2)
		 * @see vector2
		 */
		[[nodiscard]] const vector2<float>& get_half_extents() const { return half_extents_; }

	private:
		vector2<float> half_extents_ = {};
		vector2<float> top_left_ = {};
		vector2<float> bottom_right_ = {};
	};
}

#endif