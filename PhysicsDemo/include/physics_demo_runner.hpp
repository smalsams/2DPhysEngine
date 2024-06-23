#pragma once

#include <SFML/Graphics.hpp>
#include <2DPhysicsEngine.hpp>
#include <iostream>
#include <vector>
#include "body_wrapper.hpp"
#include "demo_menu.hpp"


/*
 * @brief Example app that demonstrates the 2DPhysicsEngine library
 */
class physics_demo_runner {
public:
	explicit physics_demo_runner(const sf::Vector2i window_size) : render_window_(sf::RenderWindow(sf::VideoMode(window_size.x, window_size.y), "Physics Demo")) {
		collision_resolvers_.push_back(std::make_unique<seng::impulse_collision_resolver>());
		collision_resolvers_.push_back(std::make_unique<seng::position_correction_collision_resolver>());
		world_ = seng::world(0.0f, math_consts::GRAVITY);
		for(auto&& resolver : collision_resolvers_)
		{
			world_.add_collision_resolver(resolver.get());
		}
		render_window_.setFramerateLimit(math_consts::DEFAULT_FPS);
		window_size_ = sf::Vector2f(64,36);
		object_mode_ = CIRCLE;
		if(!font_.loadFromFile(PROJECT_SOURCE_DIR + std::string("/robotoregular.ttf")))
		{
			std::cerr << "Failed to load font" << std::endl;
		}
		const float menu_width = window_size_.x * math_consts::MENU_WIDTH;
		menu_ = demo_menu(-window_size_ * 0.5f, menu_width, window_size_.y);
		render_window_.setView(sf::View(sf::Vector2f(0,0), {window_size_.x, window_size_.y}));
	}

	/*
	 * @brief handles the events on the screen, such as mouse clicks
	 */
	void handle_screen_events();
	void update_screen(sf::Time dt);
	/*
	 * @brief runs the app
	 */
	void run();
	/*
	 * @brief updates the shapes
	 */
	void update_shapes(sf::Time dt) const;

	/*
	 * @brief renders the shapes on the screen
	 */
	void render_shapes();

	static int get_random_int(int min, int max);
private:
	seng::world world_;
	std::vector<std::unique_ptr<seng::collision_resolver>> collision_resolvers_;
	sf::RenderWindow render_window_;
	std::vector<std::unique_ptr<body_wrapper>> shapes_;
	demo_menu menu_;
	object_mode object_mode_;
	sf::Vector2f window_size_;
	sf::Font font_;
	sf::Text text_;
};
