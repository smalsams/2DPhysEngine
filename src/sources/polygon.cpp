#include "polygon.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include <cassert>

using namespace seng;
body_shape::shape_type polygon::get_type() const
{
	return POLYGON;
}

rectangle_capsule polygon::get_rectangle_capsule()
{
	const auto size = vertices_.size();
	assert(size > 2);
	vector2<float> min = vertices_[0];
	vector2<float> max = vertices_[0];
	for (auto& vertex : vertices_)
	{
		if (vertex.x() < min.x())
		{
			min.set_x(vertex.x());
		}
		if (vertex.y() < min.y())
		{
			min.set_y(vertex.y());
		}
		if (vertex.x() > max.x())
		{
			max.set_x(vertex.x());
		}
		if (vertex.y() > max.y())
		{
			max.set_y(vertex.y());
		}
	}

	return { min, max };

}

circle polygon::to_circle() const
{
	return circle(vertices_[0].magnitude());
}

std::vector<vector2<float>> polygon::calculate_normals() const
{
	const auto size = vertices_.size();
	std::vector<vector2<float>> normals;
	assert(size > 2);
	for (size_t i = 0; i < size; i++)
	{
		auto& current = vertices_[i];
		auto& next = vertices_[(i + 1) % size];
		auto edge = next - current;
		normals.push_back(vector2(edge.y(), -edge.x()).normalized());
	}
	return normals;
}

std::vector<vector2<float>> polygon::calculate_normals(const std::vector<vector2<float>>& vertices)
{
	const auto size = vertices.size();
	std::vector<vector2<float>> normals;
	assert(size > 2);
	for (size_t i = 0; i < size; i++)
	{
		auto& current = vertices[i];
		auto& next = vertices[(i + 1) % size];
		auto edge = next - current;
		normals.push_back(vector2(edge.y(), -edge.x()).normalized());
	}
	return normals;
}


std::vector<vector2<float>> polygon::get_edges() const
{
	std::vector<vector2<float>> edges;
	for (size_t i = 0; i < vertices_.size(); ++i)
	{
		vector2<float> edge = vertices_[(i + 1) % vertices_.size()] - vertices_[i];
		edges.push_back(edge);
	}
	return edges;
}

manifold polygon::handle_collision(const circle& other, const transform& first_transform,
                                   const transform& other_transform) const
{
	manifold man;
	std::vector<vector2<float>> transformed_vertices;

	for (const auto& vertex : vertices_) {
		transformed_vertices.push_back(first_transform.position + vertex);
	}
	
	vector2 closest_vertex = transformed_vertices[0];
	float min_distance_squared = (other_transform.position - closest_vertex).magnitude_squared();
	for (size_t i = 1; i < transformed_vertices.size(); ++i) {
		const float distance_squared = (other_transform.position - transformed_vertices[i]).magnitude_squared();
		if (distance_squared < min_distance_squared) {
			closest_vertex = transformed_vertices[i];
			min_distance_squared = distance_squared;
		}
	}

	vector2<float> axis = (closest_vertex - other_transform.position).normalized();

	const float circle_min = other_transform.position.dot(axis) - other.get_radius();
	const float circle_max = other_transform.position.dot(axis) + other.get_radius();

	float polygon_min = std::numeric_limits<float>::max();
	float polygon_max = std::numeric_limits<float>::lowest();
	for (const auto& vertex : transformed_vertices) {
		float projection = vertex.dot(axis);
		polygon_min = std::min(polygon_min, projection);
		polygon_max = std::max(polygon_max, projection);
	}

	if (polygon_max < circle_min || circle_max < polygon_min) {
		return man;
	}

	const float penetration = std::min(circle_max - polygon_min, polygon_max - circle_min);

	if (penetration - other.get_radius() > 0) {
		return { closest_vertex, other_transform.position + axis * penetration, axis, other.get_radius()};
	}

	man.first = closest_vertex;
	man.second = other_transform.position + axis * penetration;
	man.normal = -axis;
	man.penetration = penetration;
	man.is_colliding = true;

	return man;
}

manifold polygon::handle_collision(const polygon& other, const transform& first_transform,
	const transform& other_transform) const
{
	float min_overlap = std::numeric_limits<float>::max();
	vector2<float> smallest_axis;

	for (const auto& edge : get_edges())
	{
		vector2 axis = {edge.y(), -edge.x()};
		auto [min1, max1] = project(axis, first_transform.position);
		auto [min2, max2] = other.project(axis, other_transform.position);

		if (max1 < min2 || max2 < min1)
		{
			return {};
		}

		float overlap = std::min(max1, max2) - std::max(min1, min2);
		if (overlap < min_overlap)
		{
			min_overlap = overlap;
			smallest_axis = axis;
		}
	}

	for (const auto& edge : other.get_edges())
	{
		vector2<float> axis = {edge.y(), -edge.x()};
		auto [minA, maxA] = project(axis, first_transform.position);
		auto [minB, maxB] = other.project(axis, other_transform.position);

		if (maxA < minB || maxB < minA)
		{
			return {};
		}

		const float overlap = std::min(maxA, maxB) - std::max(minA, minB);
		if (overlap < min_overlap)
		{
			min_overlap = overlap;
			smallest_axis = axis;
		}
	}

	vector2<float> first_collision_point = first_transform.position + smallest_axis * min_overlap / 2.0f;
	vector2<float> second_collision_point = other_transform.position - smallest_axis * min_overlap / 2.0f;

	return { first_collision_point, second_collision_point, smallest_axis.normalized() , min_overlap };
}

std::pair<float, float> polygon::project(const vector2<float>& axis, const vector2<float>& position) const
{
	float min = axis.dot(position + vertices_[0]);
	float max = min;

	for (size_t i = 1; i < vertices_.size(); ++i)
	{
		const float projection = axis.dot(position + vertices_[i]);

		
		if (projection < min)
		{
			min = projection;
		}
		else if (projection > max)
		{
			max = projection;
		}
	}

	return { min, max };
}

vector2<float> polygon::get_rectangle_capsule_size()
{
	return get_rectangle_capsule().get_size();
}

manifold polygon::handle_collision(const rectangle& other, const transform& this_transform,
	const transform& other_transform) const
{
	const polygon transformed_rec = other.to_polygon();
	return handle_collision(transformed_rec, this_transform, other_transform);
}
