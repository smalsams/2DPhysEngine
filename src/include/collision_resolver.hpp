#pragma once
#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP
#include <functional>
#include <map>
#include <utility>
#include <vector>

#include "collisions.hpp"

namespace seng {

	/*
	 * @brief Manages the collision between objects
	 * @see impulse_collision_manager
	 * @see position_correction_collision_manager
	 */
	class collision_resolver
	{
	public:
		collision_resolver() = default;
		virtual ~collision_resolver() = default;
		collision_resolver(const collision_resolver&) = default;
		collision_resolver(collision_resolver&&) = default;
		collision_resolver& operator=(const collision_resolver&) = delete;
		collision_resolver& operator=(collision_resolver&&) = delete;
		/*
		 * @brief Solve the collision between the objects, decides the response to the collision
		 */
		virtual void solve_collision(const std::vector<collision_data>& collisions, float dt) = 0;
	};

	class impulse_collision_resolver final : public collision_resolver
	{
	public:
		void solve_collision(const std::vector<collision_data>& collisions, float dt) override;
	};

	class position_correction_collision_resolver final : public collision_resolver
	{
		public:
		void solve_collision(const std::vector<collision_data>& collisions, float dt) override;
	};


	/*
	 * @brief Custom collision manager, allows for custom collision solving
	 * @see collision_manager
	 **/
	class custom_collision_resolver final : public collision_resolver
	{
		std::function<void(const std::vector<collision_data>&, float)> solve_collision_function_;
		void set_solve_collision_function(std::function<void(const std::vector<collision_data>&, float)> solve_collision_function);

		void solve_collision(const std::vector<collision_data>& collisions, float dt) override;
	};
}
#endif