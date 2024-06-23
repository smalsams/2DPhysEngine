#pragma once
#include "body_wrapper.hpp"

class circle_wrapper final : public body_wrapper
{
public:
	circle_wrapper(const sf::Vector2f position, float radius) : body_wrapper(position), circle_shape_(radius)
	{
		abstract_shape_ = std::make_unique<seng::circle>(radius);
		body_->set_shape(abstract_shape_.get());
		circle_shape_.setOrigin(radius, radius);
		circle_shape_.setFillColor(sf::Color::Green);
	}

	void update(sf::Time dt) override;


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::CircleShape circle_shape_;
};