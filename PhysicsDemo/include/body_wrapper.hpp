#pragma once
#ifndef BODY_WRAPPER_HPP
#define BODY_WRAPPER_HPP
#include <2DPhysicsEngine.hpp>
#include <SFML/Graphics.hpp>
/*
 * Provides a wrapper for the body class in the 2DPhysicsEngine library
 */
class body_wrapper : public sf::Drawable, public sf::Transformable
{
public:
	explicit body_wrapper(sf::Vector2f position);

	/*
	 * @brief Returns the pointer to the body object
	 */
	seng::body* get_body() const { return body_.get(); }

	/*
	 * @brief updates the screen with the body
	 */
	virtual void update(sf::Time dt) = 0;

private:
	sf::Color color_;
protected:
	std::unique_ptr<seng::body_shape> abstract_shape_;
	std::unique_ptr<seng::body> body_;
};

namespace math_consts
{
	constexpr int DEFAULT_FPS = 240;
	constexpr float MENU_WIDTH = 0.1f;
	constexpr float GRAVITY = -9.81f;
	constexpr float pi = 3.14159f;
	constexpr float tau = pi * 2;
}

#endif