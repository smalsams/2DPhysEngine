#pragma once
#ifndef MANIFOLD_HPP
#define MANIFOLD_HPP
#include "2dMath.hpp"
namespace seng {
	/*
	 * Holds the physics data for a collision between two bodies
	 *
	 */
	struct manifold
	{
		manifold(const vector2<float> first, const vector2<float> second, const vector2<float> normal,
		         const float penetration) : first(first),
		                                    second(second), normal(normal), penetration(penetration), is_colliding(true) {}
		manifold() : first(vector2<float>()), second(vector2<float>()), normal(vector2<float>()), penetration(0) {}

		/*
		 * @brief the first point of the collision
		 */
		vector2<float> first;

		/*
		 * @brief the second point of the collision
		 */
		vector2<float> second;

		/*
		 * @brief the normal of the collision
		 */
		vector2<float> normal;

		/*
		 * @brief the penetration of the collision (how much the two bodies are inside each other)
		 */
		float penetration;
		bool is_colliding{};

		manifold swap() const
		{
			return {second, first, -1 * normal, penetration};
		}
	};
}
#endif