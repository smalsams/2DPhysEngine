#pragma once

#ifndef BODY_HPP
#define BODY_HPP
#include <cmath>
#include <memory>
#include <cfloat>
#include "shape.hpp"

namespace seng {

	/*
	 * @brief Enum to represent the type of body (affects the response to the collision)
	 */
	enum class body_type
	{
		STATIC,
		DYNAMIC
	};
	class body_shape;
	/*
	 * @brief Class to represent a rigid body, a physics object
	 *
	 */
	struct body {
	public:
		body()
		{
			assign_id();
		}

		body(float x, float y) : body()
		{
			transform_ = { {x,y}, 0 };
			force_ = { 0, 0 };
			velocity_ = { 0, 0 };
			angular_velocity_ = 0.0f;
			mass_ = 1.0f;
			inverted_mass_ = 1.0f;
			type_ = body_type::DYNAMIC;
			restitution_ = 0.4f;
			friction_ = 0.1f;
		}

		explicit body(const vector2<float>& position) : body(position.x(), position.y()) {}
		/**
		 * @brief Updates the rigid body
		 * @param dt Delta time
		 */
		void update(float dt);

		//setters
		void set_position(const vector2<float>& position) { transform_.position = position; }
		void set_velocity(const vector2<float>& velocity) { velocity_ = velocity; }
		void set_angular_velocity(const float angular_velocity) { angular_velocity_ = angular_velocity; }
		void set_angle(const float angle) { transform_.angle = angle; }
		void set_mass(const float mass)
		{
			if (mass == 0)
			{
				mass_ = 0;
				inverted_mass_ = 0;
			}
			else
			{
				mass_ = mass;
				inverted_mass_ = 1 / mass;
			}
		}
		void set_gravity(const vector2<float>& gravity) { gravity_ = gravity; }
		void set_type(body_type type) { type_ = type; }
		void set_shape(body_shape* shape) { body_shape_ = shape; }
		void set_restitution(const float restitution) { restitution_ = restitution; }
		void set_friction(const float friction) { friction_ = friction; }

		//getters
		[[nodiscard]] body_type get_type() const { return type_; }
		[[nodiscard]] vector2<float> get_position() const { return transform_.position; }
		[[nodiscard]] vector2<float> get_velocity() const { return velocity_; }
		[[nodiscard]] float get_angular_velocity() const { return angular_velocity_; }
		[[nodiscard]] float get_angle() const { return transform_.angle; }
		[[nodiscard]] float get_mass() const { return mass_; }
		[[nodiscard]] float get_inv_mass() const { return inverted_mass_; }
		[[nodiscard]] float get_restitution() const { return restitution_; }
		[[nodiscard]] vector2<float> get_gravity() const { return gravity_; }
		[[nodiscard]] vector2<float> get_force() const { return force_; }
		[[nodiscard]] transform get_transform() const { return transform_; }
		[[nodiscard]] float get_friction() const { return friction_; }
		[[nodiscard]] long get_id() const { return id; }
		[[nodiscard]] body_shape* get_shape() const { return body_shape_; }

		long id;
	private:		 
		/**
		 * @brief assigns an id to the body
		 */
		body_shape* body_shape_;
		void assign_id();
		vector2<float> gravity_ = { 0, 0};
		transform transform_;
		vector2<float> velocity_;
		vector2<float> force_;

		float angular_velocity_;

		float mass_;
		float inverted_mass_;

		float friction_ = 0.0f;
		float restitution_ = 0.0f;

		body_type type_;
	};

}
#endif 