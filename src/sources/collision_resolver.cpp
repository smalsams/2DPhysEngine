#include "collision_resolver.hpp"

#include "circle.hpp"
#include "polygon.hpp"
using namespace seng;

void impulse_collision_resolver::solve_collision(const std::vector<collision_data>& collisions, float dt)
{
	for (auto&& [first, second, manifold] : collisions)
	{
		body* body_a = first->get_type() == body_type::DYNAMIC ? first : nullptr;
		body* body_b = second->get_type() == body_type::DYNAMIC ? second : nullptr;

		vector2<float> velocity_a = body_a ? body_a->get_velocity() : vector2<float>(0, 0);
		vector2<float> velocity_b = body_b ? body_b->get_velocity() : vector2<float>(0, 0);
		vector2<float> relative_velocity = velocity_b - velocity_a;
		const float velocity_at_normal = relative_velocity.dot(manifold.normal);
		if(velocity_at_normal >= 0)
		{
			return;
		}
		const float inverse_mass_a = body_a ? body_a->get_inv_mass() : 0.0f;
		const float inverse_mass_b = body_b ? body_b->get_inv_mass() : 0.0f;



		auto restitution_a = body_a ? body_a->get_restitution() : 1.0f;
		auto restitution_b = body_b ? body_b->get_restitution() : 1.0f;
		//source:Wikipedia
		const auto min_restitution = std::min(restitution_a, restitution_b);
		const float impulse_scalar = (-(1 + min_restitution) * velocity_at_normal) / (inverse_mass_a + inverse_mass_b);
		vector2<float> impulse = impulse_scalar * manifold.normal;
		if (body_a)
		{
			body_a->set_velocity(velocity_a - impulse * inverse_mass_a);
		}
		if (body_b)
		{
			body_b->set_velocity(velocity_b + impulse * inverse_mass_b);
		}
		
	}
}

void position_correction_collision_resolver::solve_collision(const std::vector<collision_data>& collisions, float dt)
{
	for (auto&& [first, second, manifold] : collisions)
	{
		body* body_a = first->get_type() == body_type::DYNAMIC ? first : nullptr;
		body* body_b = second->get_type() == body_type::DYNAMIC ? second : nullptr;
		const auto inv_mass_a = body_a ? body_a->get_inv_mass() : 1.0f;
		const auto inv_mass_b = body_b ? body_b->get_inv_mass() : 1.0f;
		constexpr float percent = 0.2f;
		constexpr float slope = 0.01f;
		const vector2<float> correction = std::max(manifold.penetration - slope, 0.0f) / (inv_mass_a + inv_mass_b) * percent * manifold.normal;
		if (body_a)
		{
			body_a->set_position(body_a->get_position() - correction * inv_mass_a);
		}
		if (body_b)
		{
			body_b->set_position(body_b->get_position() + correction * inv_mass_b);
		}
	}
}

void custom_collision_resolver::set_solve_collision_function(
	std::function<void(const std::vector<collision_data>&, float)> solve_collision_function)
{
	solve_collision_function_ = std::move(solve_collision_function);
}

void custom_collision_resolver::solve_collision(const std::vector<collision_data>& collisions, float dt)
{
	solve_collision_function_(collisions, dt);
}

