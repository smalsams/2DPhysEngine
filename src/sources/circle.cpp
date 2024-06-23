#include "circle.hpp"
#include "polygon.hpp"
#include "rectangle.hpp"
using namespace seng;
body_shape::shape_type circle::get_type() const
{
	return CIRCLE;
}

rectangle_capsule circle::get_rectangle_capsule()
{
	return { vector2(-radius_, -radius_), vector2(radius_, radius_) };
}


manifold circle::handle_collision(const circle& other, const transform& first_transform,
	const transform& other_transform) const
{
	vector2<float> first_pos = first_transform.position;
	vector2<float> second_pos = other_transform.position;
	const vector2<float> first_to_second = second_pos - first_pos;
	const vector2<float> second_to_first = first_pos - second_pos;
	if(first_to_second.magnitude() >= radius_ + other.radius_)
	{
		return {};
	}
	const vector2<float> new_mag_first = first_to_second * radius_ / first_to_second.magnitude();
	const vector2<float> new_mag_second = second_to_first * other.radius_ / second_to_first.magnitude();
	first_pos += new_mag_first;
	second_pos += new_mag_second;
	const vector2<float> dist = second_pos - first_pos;
	return {first_pos, second_pos, -dist.normalized(), dist.magnitude() };
}

manifold circle::handle_collision(const polygon& other, const transform& first_transform,
	const transform& other_transform) const
{
	return other.handle_collision(*this, other_transform, first_transform).swap();
}

vector2<float> circle::get_rectangle_capsule_size()
{
	return { 2 * radius_, 2 * radius_ };
}

manifold circle::handle_collision(const rectangle& other, const transform& this_transform,
	const transform& other_transform) const
{
	return other.handle_collision(*this, other_transform, this_transform).swap();
}
