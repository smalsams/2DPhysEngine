#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <vector>
#include <unordered_map>

#include "collision_grid.hpp"
#include "collision_resolver.hpp"
#include "logger.hpp"

namespace seng
{
	/*
	 * @brief The world class is the main class of the physics engine, it contains all the bodies and collision managers
	 */
	class world
	{
	public:
		world() : world({}, {}, {0, -9.81f}) {}
		explicit world(const vector2<float> gravity) : world({}, {}, gravity) {}
		world(const float x_gravity, const float y_gravity) : world(vector2{ x_gravity, y_gravity }) {}
		world(const std::unordered_map<long, body*>& bodies, const std::vector<collision_resolver*>& collision_managers, vector2<float> gravity) :
			bodies_(bodies),
			gravity_(gravity),
			collision_grid_({-200, -200}, {200,200}, 5),
			collision_managers_(collision_managers) {}

		/*
		 * @brief updates the world and its contents per unit of time
		 * @param dt Delta time
		 **/
		void update_world(const float dt);

		/*
		 * @brief adds a body to the world
		 * @param body the body to add (has to be a valid pointer)
		 */
		void add_body(body* body);
		/*
		 * @brief adds a collision manager to the world
		 * @param collision_manager the collision manager to add (has to be a valid pointer)
		 */
		void add_collision_resolver(collision_resolver* collision_manager);

		/*
		 * @brief clears the world of all bodies
		 */
		void clear();

		/*
		 * @brief gets the collisions between two bodies, if both bodies are colliding
		 * @param id1 the id of the first body
		 * @param id2 the id of the second body
		 * @param collision_datas the vector to store the collision data in
		 */
		void get_collisions(const long id1, const long id2, std::vector<collision_data>& collision_datas);

		/*
		 * @brief calls the solve_collision method of the collision managers, basically managing the collisions
		 * @param dt Delta time
		 * @see collision_manager::solve_collision
		 * @see impulse_collision_manager::solve_collision
		 * @see position_correction_collision_manager::solve_collision
		 */
		void manage_collisions(const float dt);

		void remove_body(const body* body)
		{
			if (body)
			{
				bodies_.erase(body->id);
			}
		}
	private:
		std::unordered_map<long, body*> bodies_;
		vector2<float> gravity_;
		collision_grid collision_grid_;
		std::vector<collision_resolver*> collision_managers_;
	};
}

#endif 