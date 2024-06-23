#pragma once
#ifndef VECTOR_ADAPTER_HPP
#define VECTOR_ADAPTER_HPP
#include <SFML/Graphics.hpp>
#include <2DPhysicsEngine.hpp>

inline sf::Vector2f to_sf_vector2_f(const seng::vector2<float> vector)
{
	return {vector.x(), vector.y()};
}

inline seng::vector2<float> to_seng_vector2(const sf::Vector2f vector)
{
	return { vector.x, vector.y };
}

inline seng::vector2<float> to_positional_vector(const sf::Vector2f vector)
{
	return { vector.x, -vector.y };
}

inline sf::Vector2f to_sf_positional_vector(const seng::vector2<float> vector)
{
	return {vector.x(), -vector.y()};
}

#endif