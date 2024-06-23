#pragma once

#ifndef COLLISION_GRID_HPP
#define COLLISION_GRID_HPP
#include <unordered_map>
#include <vector>

#include "body.hpp"

namespace seng {
	/*
	* creates a grid for collision detection during the broad phase
	* effectively reduces the number of checks needed to be made
	*/
	class collision_grid
	{
		using grid = std::vector<std::vector<std::vector<body*>>>;
	public:
		collision_grid(const vector2<float> topleft, const vector2<float> bottomright, float cell_size);

		/*
		* @brief updates the grid with the new positions of the bodies
		* @param bodies the bodies to update the grid with
		*/
		void update_grid(const std::unordered_map<long, body*>& bodies);
		/*
		 gets the pairs of objects in the same cell
		*/
		[[nodiscard]] std::vector<std::pair<long, long>> get_collision_indices() const;

		/*
		 * @brief checks if a position is out of the grid
		 * @param position the position to check
		 */
		[[nodiscard]] bool out_of_bound(const vector2<float>& position) const;

		/*
		 * @brief remaps the body positions to the grid cells
		 */
		void reinitialize_grid();

		/*
		 * @brief gets the minimum cell position of the body
		 */
		vector2<int> get_cell_min(const vector2<float>& position, const vector2<float>& size) const;

		/*
		 * @brief gets the maximum cell position of the body
		 */
		vector2<int> get_cell_max(const vector2<float>& position, const vector2<float>& size) const;

	private:
		float cell_size_;
		vector2<float> topleft_;
		vector2<float> bottomright_;
		long width_;
		long height_;
		grid grid_;
	};
}
#endif