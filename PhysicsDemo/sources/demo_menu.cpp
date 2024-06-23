#include "demo_menu.hpp"


constexpr float BUTTON_OFFSET = 0.1f;
constexpr float BUTTON_HEIGHT = 5.0f;
constexpr float BUTTON_WIDTH_SCALE = 0.8f;
constexpr float CIRCLE_OFFSET = 1.0f;
constexpr float RECTANGLE_OFFSET = 1.5f;
constexpr float CIRCLE_RADIUS = 1.5f;
constexpr float RECTANGLE_X_Y = 2.0f;

demo_menu::demo_menu(sf::Vector2f position, float width, float height): position_(position), width_(width), height_(height)
{
	background_.setPosition(position_);
	background_.setSize(sf::Vector2f(width_, height_));
	background_.setFillColor(sf::Color::White);
	background_.setOutlineColor(sf::Color::Red);
	background_.setOutlineThickness(0.2f);
	auto rectangle_button_shape = sf::RectangleShape(sf::Vector2f(RECTANGLE_X_Y, RECTANGLE_X_Y));
	auto circle_button_shape = sf::CircleShape(CIRCLE_RADIUS);
	auto polygon_button_shape = sf::ConvexShape(3);
	polygon_button_shape.setPoint(0, { 1, 3 });
	polygon_button_shape.setPoint(1, { 0, 0 });
	polygon_button_shape.setPoint(2, { 2,1 });
	circle_button_shape.setOutlineColor(sf::Color::White);
	rectangle_button_shape.setOutlineColor(sf::Color::White);
	polygon_button_shape.setOutlineColor(sf::Color::White);
	rectangle_button_shape.setPosition(position.x + width_ * BUTTON_OFFSET + RECTANGLE_OFFSET, position.y + height / 4);
	circle_button_shape.setPosition(position.x + width_ * BUTTON_OFFSET + CIRCLE_OFFSET, position.y + height / 2);
	polygon_button_shape.setPosition(position.x + width_ * BUTTON_OFFSET + CIRCLE_OFFSET, position.y + height / 4 * 3);
	circle_button_shape.setFillColor(sf::Color::Red);
	rectangle_button_shape.setFillColor(sf::Color::Cyan);
	polygon_button_shape.setFillColor(sf::Color::Magenta);
	buttons_.emplace_back(std::move(rectangle_button_shape), sf::Vector2f(position.x + width_ * BUTTON_OFFSET, position.y + height / 4 - 1.5f), sf::Vector2f(width_ * BUTTON_WIDTH_SCALE, BUTTON_HEIGHT));
	buttons_.emplace_back(std::move(circle_button_shape), sf::Vector2f(position.x + width_ * BUTTON_OFFSET,position.y + height / 2 - 1), sf::Vector2f(width_ * BUTTON_WIDTH_SCALE, BUTTON_HEIGHT));
	buttons_.emplace_back(std::move(polygon_button_shape), sf::Vector2f(position.x + width_ * BUTTON_OFFSET, position.y + height / 4 * 3 - 1), sf::Vector2f(width_ * BUTTON_WIDTH_SCALE, BUTTON_HEIGHT));
}

void demo_menu::draw(sf::RenderWindow& window) const
{
	window.draw(background_);
	for (const auto& button : buttons_)
	{
		button.draw(window);
	}
}

object_mode demo_menu::get_object_mode(const sf::Vector2f position, const object_mode current) const
{
	for (const auto& button : buttons_)
	{
		if (button.is_clicked(position))
		{
			return button.get_object_mode();
		}
	}
	return current;
}
