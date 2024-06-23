#pragma once
#ifndef POLYGON_WRAPPER_HPP
#define POLYGON_WRAPPER_HPP
#include "body_wrapper.hpp"

class polygon_wrapper final : public body_wrapper
{
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:

	polygon_wrapper(sf::Vector2f position, size_t vertex_count, float radius, float default_angle = math_consts::pi/2) : body_wrapper(position)
	{
		float angle = default_angle / math_consts::pi;
		float default_first = math_consts::tau / static_cast<float>(vertex_count);

		polygon_shape_.setPointCount(vertex_count);
		std::vector<seng::vector2<float>> points;
		for (size_t i = 0; i < vertex_count; i++)
		{
			float x_dist = std::cos(angle) * radius;
			float y_dist = std::sin(angle) * radius;

			polygon_shape_.setPoint(i, { x_dist, y_dist});
			points.emplace_back(x_dist, -y_dist);
			angle += default_first;
		}
		polygon_shape_.setFillColor(sf::Color::Red);
		abstract_shape_ = std::make_unique<seng::polygon>(points);
		body_->set_shape(abstract_shape_.get());
	}

	void update(sf::Time dt) override;
private:
	sf::ConvexShape polygon_shape_;
};

#endif