#pragma once
#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace seng {
	class rectangle_capsule;
	class circle final : public body_shape {
	public:
		explicit circle(const float radius) : radius_(radius)
		{
		}
		[[nodiscard]] shape_type get_type() const override;
		rectangle_capsule get_rectangle_capsule() override;

		[[nodiscard]] float get_radius() const { return radius_; }
		[[nodiscard]] manifold handle_collision(const circle& other, const transform& first_transform, const transform& other_transform) const override;
		[[nodiscard]] manifold handle_collision(const polygon& other, const transform& first_transform, const transform& other_transform) const override;
		[[nodiscard]] manifold handle_collision(const rectangle& other, const transform& this_transform,
		                                           const transform& other_transform) const override;
		vector2<float> get_rectangle_capsule_size() override;

	private:
		float radius_;
	};
}

#endif