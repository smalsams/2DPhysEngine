#pragma once
#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP
#include "body.hpp"
#include "manifold.hpp"

namespace seng {

	/*
	 * Holds the abstract data for a collision between two bodies
	 */
	struct collision_data
	{
		body* first{};
		body* second{};
		manifold manifold_;

		collision_data(body* f, body* s, manifold man) : first(f), second(s), manifold_(man){}
	};
}
#endif