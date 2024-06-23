#pragma once
#ifndef RECTANGLE_WRAPPER_HPP
#define RECTANGLE_WRAPPER_HPP
#include "body_wrapper.hpp"
#include "vector_adapter.hpp"

class rectangle_wrapper final : public body_wrapper
{
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	rectangle_wrapper(const sf::Vector2f position, const sf::Vector2f size) : body_wrapper(position), rectangle_shape_(size)
	{
		abstract_shape_ = std::make_unique<seng::rectangle>(to_seng_vector2(size));
		body_->set_shape(abstract_shape_.get());
		rectangle_shape_.setOrigin(size.x / 2, size.y / 2);
		rectangle_shape_.setFillColor(sf::Color::Blue);
	}
	void update(sf::Time dt) override;
private:
	sf::RectangleShape rectangle_shape_;
};
#endif