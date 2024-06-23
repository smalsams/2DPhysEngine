#include "collision_grid.hpp"

using namespace seng;

collision_grid::collision_grid(const vector2<float> topleft,const vector2<float> bottomright, float cell_size)
{
	topleft_ = topleft;
	bottomright_ = bottomright;
	cell_size_ = cell_size;
	width_ = static_cast<long>(std::floor ((bottomright_.x() - topleft_.x()) / cell_size_));
	height_ = static_cast<long>(std::floor((bottomright_.y() - topleft_.y()) / cell_size_));
}

void collision_grid::update_grid(const std::unordered_map<long, body*>& bodies)
{
	reinitialize_grid();
	for(auto&& [id, body] : bodies)
	{
		const auto& position = body->get_position();
		const auto shape = body->get_shape();
		if (!shape)
		{
			continue;
		}
		auto real_position = (position + shape->center);
		if (out_of_bound(real_position))
		{
			continue;
		}
		auto size = shape->get_rectangle_capsule_size();

		auto cell_position_min = get_cell_min(real_position, size);
		auto cell_position_max = get_cell_max(real_position, size);

		for (int i = cell_position_min.x(); i <= cell_position_max.x(); i++)
		{
			if (grid_[i].empty())
			{
				grid_[i].resize(static_cast<int>(height_));
			}
			std::vector<std::vector<seng::body*>>& column = grid_[i];

			for (int j = cell_position_min.y(); j <= cell_position_max.y(); j++)
			{
				std::vector<seng::body*>& cell = column[j];
				cell.push_back(body);
			}
		}

	}
}


std::vector<std::pair<long,long>> collision_grid::get_collision_indices() const
{
	std::vector<std::pair<long, long>> collision_indices;
	std::unordered_multimap<body*, body*> pairs;
	auto checked = [](const std::unordered_multimap<body*, body*>& pair_map, const std::pair<body*, body*>& pair) -> bool
	{
		auto [first, second] = pair_map.equal_range(pair.first);
		bool is_checked = false;
		for (auto it = first; it != second; ++it)
		{
			if (it->second == pair.second)
			{
				is_checked = true;
				break;
			}
		}
		return is_checked;
	};
	for (auto&& column : grid_)
	{
		for (auto&& cell : column)
		{
			for (size_t i = 0; i < cell.size(); i++)
			{
				body* first = cell[i];
				for (size_t j = i + 1; j < cell.size(); j++)
				{
					body* second = cell[j];
					auto pair = first < second ?  std::make_pair(first, second) : std::make_pair(second, first);
					if (!checked(pairs, pair))
					{
						pairs.insert(pair);
						collision_indices.emplace_back(first->id, second->id);
					}
				}
			}
		}
	}
	return collision_indices;
}

bool collision_grid::out_of_bound(const vector2<float>& position) const
{
	return position.x() < topleft_.x() || position.x() > bottomright_.x() || position.y() < topleft_.y() || position.y() > bottomright_.y();
}

void collision_grid::reinitialize_grid()
{
	grid_.clear();
	grid_.resize(static_cast<int>(width_));
}

vector2<int> collision_grid::get_cell_min(const vector2<float>& position, const vector2<float>& size) const
{
	auto cell_position_min = ((position - size - topleft_) * (1 / cell_size_)).floor();
	cell_position_min.set_x(std::clamp(cell_position_min.x(), 0, static_cast<int>(width_)));
	cell_position_min.set_y(std::clamp(cell_position_min.y(), 0, static_cast<int>(height_)));
	return cell_position_min;
}

vector2<int> collision_grid::get_cell_max(const vector2<float>& position, const vector2<float>& size) const
{
	auto cell_position_max = ((position + size - topleft_) * (1 / cell_size_)).floor();
	cell_position_max.set_x(std::clamp(cell_position_max.x(), 0, static_cast<int>(width_) - 1));
	cell_position_max.set_y(std::clamp(cell_position_max.y(), 0, static_cast<int>(height_) - 1));
	return cell_position_max;
}
