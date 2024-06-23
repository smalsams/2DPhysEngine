#include "physics_demo_runner.hpp"

#include <random>

#include "circle_wrapper.hpp"
#include "polygon_wrapper.hpp"
#include "rectangle_wrapper.hpp"

void physics_demo_runner::handle_screen_events()
{
	sf::Event event;
	while (render_window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			render_window_.close();
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			const auto mouse_position = sf::Mouse::getPosition(render_window_);
			const auto pixel = render_window_.mapPixelToCoords(mouse_position);
			if (pixel.x < 0.1 * window_size_.x + -window_size_.x / 2.0f)
			{
				object_mode_ = menu_.get_object_mode(pixel, object_mode_);
				continue;
			}
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (object_mode_ == CIRCLE)
				{
					auto circle = std::make_unique<circle_wrapper>(sf::Vector2f(pixel.x , -pixel.y), static_cast<float>(get_random_int(1, 8)) / 2.0f);
					world_.add_body(circle->get_body());
					shapes_.push_back(std::move(circle));
				}
				if (object_mode_ == RECTANGLE)
				{
					auto rectangle = std::make_unique<rectangle_wrapper>(
						sf::Vector2f(pixel.x, -pixel.y),
						sf::Vector2f(static_cast<float>(get_random_int(2, 10)) / 2.0f, static_cast<float>(get_random_int(2, 10)) / 2.0f));
					world_.add_body(rectangle->get_body());
					shapes_.push_back(std::move(rectangle));
				}
				if (object_mode_ == POLYGON)
				{
					auto polygon = std::make_unique<polygon_wrapper>(sf::Vector2f(pixel.x, -pixel.y), 3, get_random_int(4,8) / 4);
					world_.add_body(polygon->get_body());
					shapes_.push_back(std::move(polygon));
				}
			}
		}
	}
}

void physics_demo_runner::update_screen(sf::Time dt)
{
	world_.update_world(dt.asSeconds());
	update_shapes(dt);
	render_window_.clear();
	render_shapes();
	menu_.draw(render_window_);
	render_window_.draw(text_);
	render_window_.display();
}

void physics_demo_runner::run()
{
	sf::Clock clock;

	text_ = sf::Text("Current object count: " + std::to_string(shapes_.size()), font_, 12);
	text_.setPosition(0.25f * window_size_.x, -0.45f * window_size_.y);
	text_.setScale(0.1f, 0.1f);
	object_mode_ = CIRCLE;
	auto example_circle_position = sf::Vector2f(0.0, -0.3f * window_size_.y);
	auto example_circle = std::make_unique<circle_wrapper>(example_circle_position, 7.0f);
	example_circle->get_body()->set_type(seng::body_type::STATIC);
	example_circle->get_body()->set_mass(std::numeric_limits<float>::max());
	auto example_rectangle_position = sf::Vector2f(-15.0f, -0.4f * window_size_.y);
	auto example_rectangle = std::make_unique<rectangle_wrapper>(example_rectangle_position, sf::Vector2f(4,2) );
	example_rectangle->get_body()->set_type(seng::body_type::STATIC);
	example_rectangle->get_body()->set_mass(std::numeric_limits<float>::max());
	world_.add_body(example_rectangle->get_body());
	shapes_.push_back(std::move(example_rectangle));
	world_.add_body(example_circle->get_body());
	shapes_.push_back(std::move(example_circle));
	while(render_window_.isOpen())
	{
		const sf::Time dt = clock.restart();
		handle_screen_events();
		text_.setString("Current object count: " + std::to_string(shapes_.size()));
		update_screen(dt);
	}
}

void physics_demo_runner::update_shapes(const sf::Time dt) const
{
	for(auto&& shape : shapes_)
	{
		shape->update(dt);
	}
}

void physics_demo_runner::render_shapes() 
{
	for(auto&& shape : shapes_)
	{
		render_window_.draw(*shape);
	}
}

int physics_demo_runner::get_random_int(const int min, const int max)
{
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution distribution(min, max);
	return distribution(gen);
}
