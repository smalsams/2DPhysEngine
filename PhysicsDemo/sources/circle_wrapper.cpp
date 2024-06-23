#include "circle_wrapper.hpp"

#include "vector_adapter.hpp"


void circle_wrapper::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(circle_shape_, states);
}

void circle_wrapper::update(sf::Time dt) 
{
	setPosition(to_sf_positional_vector(body_->get_position()));
	setRotation(body_->get_angle());
}
