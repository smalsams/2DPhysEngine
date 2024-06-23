#include "body.hpp"
using namespace seng;

void body::update(float dt) {
	if (type_ == body_type::STATIC)
	{
		return;
	}
	force_ += gravity_ * mass_;

	//apply forces
	velocity_ += force_ * inverted_mass_ * dt;
	transform_.position += velocity_ * dt;
	transform_.angle += angular_velocity_ * dt;
	force_ = { 0,0 };
}

void body::assign_id()
{
	static long id_counter = 0;
	id = id_counter++;
}



