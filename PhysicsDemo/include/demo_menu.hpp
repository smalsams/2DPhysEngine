#pragma once
#ifndef DEMO_MENU_HPP
#define DEMO_MENU_HPP
#include "button.hpp"

/*
 * @brief Class for the demo menu that is displayed in the top left corner of the screen
 */
class demo_menu {
public:
	demo_menu() : width_(0), height_(0) {}
	demo_menu(sf::Vector2f position, float width, float height);
	void draw(sf::RenderWindow& window) const;
	/*
	 * @brief Get the object mode based on the button clicked
	 */
	object_mode get_object_mode(sf::Vector2f position, object_mode current) const;
private:
	sf::RectangleShape background_;
	sf::Vector2f position_;
	float width_;
	float height_;
	std::vector<button> buttons_;
};
#endif