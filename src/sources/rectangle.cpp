#include "rectangle.hpp"
#include "circle.hpp"
#include "polygon.hpp"
using namespace seng;

body_shape::shape_type rectangle::get_type() const
{
	return RECTANGLE;
}

polygon rectangle::to_polygon() const
{
	const auto first = top_left_;
	const auto second = top_left_ + vector2(half_extents_.x() * 2, 0.0f);
	const auto third = bottom_right_;
	const auto fourth = top_left_ + vector2(0.0f, half_extents_.y() * 2);
	std::vector vertices = {first, second, third, fourth };
	return { vertices };
}

rectangle_capsule rectangle::get_rectangle_capsule()
{
	return { top_left_, bottom_right_ };
}

manifold rectangle::handle_collision(const circle& other, const transform& this_transform,
	const transform& other_transform) const
{
	const vector2<float> rectangle_pos = this_transform.position;
	const vector2<float> circle_pos = other_transform.position;
	const vector2<float> first_to_second = circle_pos - rectangle_pos;
	const float radius = other.get_radius();
	vector2 point = {
		std::clamp(first_to_second.x(), -half_extents_.x(), half_extents_.x()),
		std::clamp(first_to_second.y(), -half_extents_.y(), half_extents_.y())
	};
	bool inside = false;
	if(almost_equal(point, first_to_second, 0.01f))
	{
		inside = true;
		const vector2<float> positive_distances = (half_extents_ - point).fabs();
		const vector2<float> negative_distances = (half_extents_ + point).fabs();
		const float min_distance = single_min(positive_distances, negative_distances);
		if (almost_equal(min_distance, positive_distances.x(), 0.01f))
		{
			point.set_x(half_extents_.x());
		}
		else if(almost_equal(min_distance, positive_distances.y(), 0.01f))
		{
			point.set_y(half_extents_.y());
		}
		else if (almost_equal(min_distance, negative_distances.x(), 0.01f))
		{
			point.set_x(-half_extents_.x());
		}
		else if (almost_equal(min_distance, negative_distances.y(), 0.01f))
		{
			point.set_y(-half_extents_.y());
		}
	}
	vector2<float> rectangle_collision_point = point + rectangle_pos;
	const vector2<float> dist_circle = rectangle_collision_point - circle_pos;
	if (!inside && dist_circle.magnitude() > radius)
	{
		return {};
	}
	const vector2<float> circle_dist_new = dist_circle * radius / dist_circle.magnitude();
	vector2<float> collision_point2 = circle_pos + circle_dist_new;
	if (inside)
	{
		collision_point2 = -collision_point2;
	}
	const vector2<float> dist = collision_point2 - rectangle_collision_point;
	return { rectangle_collision_point, collision_point2, -dist.normalized(), dist.magnitude() };
}

manifold rectangle::handle_collision(const polygon& other, const transform& this_transform,
	const transform& other_transform) const
{
	return other.handle_collision(this->to_polygon(), other_transform, this_transform);
}

vector2<float> rectangle::get_rectangle_capsule_size()
{
	return { half_extents_.x() * 2, half_extents_.y() * 2 };
}

manifold rectangle::handle_collision(const rectangle& other, const transform& this_transform,
	const transform& other_transform) const
{
	const vector2<float> other_pos = this_transform.position;
	const vector2<float> first_pos = other_transform.position;
	const vector2<float> other_half_extents = half_extents_;
	const vector2<float> first_half_extents = other.get_half_extents();


	const vector2<float> first_to_second = other_pos - first_pos;
	const float x_overlap = first_half_extents.x() + other_half_extents.x() - std::abs(first_to_second.x());
	if (x_overlap <= 0)
	{
		return {};
	}
	const float y_overlap = first_half_extents.y() + other_half_extents.y() - std::abs(first_to_second.y());
	if (y_overlap <= 0)
	{
		return {};
	}
	vector2<float> normal;
	vector2<float> contact_point1;
	vector2<float> contact_point2;
	if (x_overlap > y_overlap)
	{
		if (first_to_second.x() <= 0)
		{
			contact_point1.set_x(other_pos.x() - other_half_extents.x() + x_overlap / 2.0f);
			contact_point2.set_x(other_pos.x() - other_half_extents.x() + x_overlap / 2.0f);
		}
		else
		{
			contact_point1.set_x(other_pos.x() + other_half_extents.x() - x_overlap / 2.0f);
			contact_point2.set_x(other_pos.x() + other_half_extents.x() - x_overlap / 2.0f);
		}
		if (first_to_second.y() <= 0)
		{
			contact_point1.set_y(first_pos.y() - first_half_extents.y());
			contact_point2.set_y(other_pos.y() + other_half_extents.y());
			normal = { 0, 1 };
		}
		else
		{
			contact_point1.set_y(first_pos.y() + first_half_extents.y());
			contact_point2.set_y(other_pos.y() - other_half_extents.y());
			normal = { 0, -1 };
		}
		return { contact_point1, contact_point2, normal, y_overlap };
	}
	if (first_to_second.y() <= 0)
	{
		contact_point1.set_y(other_pos.y() - other_half_extents.y() + y_overlap / 2.0f);
		contact_point2.set_y(other_pos.y() - other_half_extents.y() + y_overlap / 2.0f);
	}
	else
	{
		contact_point1.set_y(other_pos.y() + other_half_extents.y() - y_overlap / 2.0f);
		contact_point2.set_y(other_pos.y() + other_half_extents.y() - y_overlap / 2.0f);
	}
	if (first_to_second.x() <= 0)
	{
		contact_point1.set_x(first_pos.x() - first_half_extents.x());
		contact_point2.set_x(other_pos.x() + other_half_extents.x());
		normal = { 1, 0 };
	}
	else
	{
		contact_point1.set_x(first_pos.x() + first_half_extents.x());
		contact_point2.set_x(other_pos.x() - other_half_extents.x());
		normal = { -1, 0 };
	}
	return { contact_point1, contact_point2, normal, x_overlap };
}
