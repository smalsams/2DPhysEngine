#pragma once
#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <variant>
#include <SFML/Graphics.hpp>

/*
 * @brief Represents the type of the object on screen and mode of the demo (creation of object on screen)
 */
enum object_mode
{
	POLYGON,
	CIRCLE,
	RECTANGLE
};

/*
 * @brief Represents a button on the screen
 */
class button {
public:
	using button_shape = std::variant<sf::RectangleShape, sf::CircleShape, sf::ConvexShape>;
	button(button_shape content, const sf::Vector2f position, const sf::Vector2f size) : content_(std::move(content)), position_(position)
	{
		shape_.setSize(size);
		shape_.setPosition(position_);
		shape_.setFillColor(sf::Color::Transparent);
		shape_.setOutlineColor(sf::Color::Black);
		shape_.setOutlineThickness(0.1f);
	}
	/*
	 * @brief Draws the button on the screen including the shape and the content
	 */
	void draw(sf::RenderTarget& target) const;
	/*
	 * @brief Checks if the button is clicked
	 * @param mouse_position The position of the mouse
	 * @return True if the button is clicked, false otherwise
	 */			 
	bool is_clicked(sf::Vector2f mouse_position) const;
	/*
	 * @brief Gets the object mode of the button
	 * @return The object mode of the button
	 * @see object_mode
	 */
	object_mode get_object_mode() const;

private:
	button_shape content_;
	sf::Vector2f position_;
	sf::RectangleShape shape_;

};



#endif
