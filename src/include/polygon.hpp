#pragma once
#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>

#include "shape.hpp"

namespace seng {
	/*
	 * @brief a class representing a convex regular polygon
	 */
	class polygon final : public body_shape {
	public:
		polygon() = default;
		polygon(const std::vector<vector2<float>>& vertices) : vertices_(vertices){}

		/*
		 * @copydoc body_shape::get_type
		 */
		[[nodiscard]] shape_type get_type() const override;

		/*
		 * @copydoc body_shape::get_rectangle_capsule
		 */
		rectangle_capsule get_rectangle_capsule() override;

		/*
		 * @brief creates a circle through the regular polygon's vertices
		 */
		[[nodiscard]] circle to_circle() const;

		/*
		 * @brief calculates normals for the polygon's edges
		 */
		[[nodiscard]] std::vector<vector2<float>> calculate_normals() const;

		/*
		 * @brief calculates normals for a custom vector of vertices
		 * (assuming that the vertices form a ring and are in a proper order)
		 */
		static std::vector<vector2<float>> calculate_normals(const std::vector<vector2<float>>& vertices);
		/*
		 * @brief getter for the vertices
		 */
		[[nodiscard]] std::vector<vector2<float>> get_vertices() const { return vertices_; }
		[[nodiscard]] std::vector<vector2<float>> get_edges() const;
		[[nodiscard]] manifold handle_collision(const circle& other, const transform& first_transform, const transform& other_transform) const override;
		[[nodiscard]] manifold handle_collision(const polygon& other, const transform& first_transform, const transform& other_transform) const override;
		vector2<float> get_rectangle_capsule_size() override;
		[[nodiscard]] manifold handle_collision(const rectangle& other, const transform& this_transform,
		                                           const transform& other_transform) const override;

		/*
		 * @brief projects a polygon onto an axis
		 */

		std::pair<float, float> project(const vector2<float>& axis, const vector2<float>& position) const;


	private:
		std::vector<vector2<float>> vertices_;
		std::vector<vector2<float>> normals_;
	};
}
#endif