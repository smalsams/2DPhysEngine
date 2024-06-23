#include "polygon_wrapper.hpp"

#include "vector_adapter.hpp"

void polygon_wrapper::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(polygon_shape_, states);
}

void polygon_wrapper::update(sf::Time dt)
{
	setPosition(to_sf_positional_vector(body_->get_position()));
	setRotation(body_->get_angle());
}
