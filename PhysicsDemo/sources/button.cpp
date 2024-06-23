#include "button.hpp"

void button::draw(sf::RenderTarget& target) const
{
	target.draw(shape_);
	std::visit([&target](auto&& arg) { target.draw(arg); }, content_);
}

bool button::is_clicked(const sf::Vector2f mouse_position) const
{
	return shape_.getGlobalBounds().contains(mouse_position);
}

object_mode button::get_object_mode() const
{
	if (std::holds_alternative<sf::RectangleShape>(content_))
	{
		return RECTANGLE;
	}
	if (std::holds_alternative<sf::CircleShape>(content_))
	{
		return CIRCLE;
	}
	return POLYGON;
}
