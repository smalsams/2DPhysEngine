#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "polygon.hpp"

seng::manifold seng::body_shape::collision(const body_shape& other, const transform& this_transform,
	const transform& other_transform) const
{
	switch (other.get_type())
	{
	case CIRCLE:
		return handle_collision(static_cast<const circle&>(other), this_transform, other_transform);
	case POLYGON:
		return handle_collision(static_cast<const polygon&>(other), this_transform, other_transform);
	case RECTANGLE:
		return handle_collision(static_cast<const rectangle&>(other), this_transform, other_transform);
	default:
		return {};
	}
}
