#include "world.hpp"
using namespace seng;


void world::add_body(body* body)
{
	if(!body)
	{
		return;
	}
	body->set_gravity(gravity_);
	bodies_.emplace(body->id, body);
}

void world::add_collision_resolver(collision_resolver* collision_manager)
{
	if(!collision_manager)
	{
		return;
	}
	collision_managers_.emplace_back(collision_manager);
}

void world::clear()
{
	bodies_.clear();
}

void world::update_world(const float dt)
{
	manage_collisions(dt);
	for (auto&& [first, second] : bodies_)
	{
		second->update(dt);
	}
}


void world::get_collisions(const long id1, const long id2, std::vector<collision_data>& collision_datas)
{
	body* body1 = bodies_[id1];
	body* body2 = bodies_[id2];
	if (!body1 || !body2)
	{
		return;
	}
	if (!body1->get_shape() || !body2->get_shape())
	{
		return;
	}
	const manifold col_manifold = body1->get_shape()->collision(*body2->get_shape(), body1->get_transform(), body2->get_transform());
	if (!col_manifold.is_colliding)
	{
		return;
	}
	collision_datas.emplace_back(body1, body2, col_manifold);
}

void world::manage_collisions(const float dt)
{
	std::vector<collision_data> collisions;
	collision_grid_.update_grid(bodies_);
	auto collision_indices = collision_grid_.get_collision_indices();
	for (auto&& [first, second] : collision_indices)
	{
		get_collisions(first, second, collisions);
	}
	for (auto&& collision_manager : collision_managers_)
	{
		collision_manager->solve_collision(collisions, dt);
	}
}





