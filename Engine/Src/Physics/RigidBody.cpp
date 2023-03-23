#include "RigidBody.h"

namespace Phys
{
	RigidBody::RigidBody(float m, Vec2& pos, Vec2 v, Vec2 a)
		: position(pos)
		, velocity(v)
		, acceleration(a)
		, mass(m)
	{}
	void RigidBody::Process(float dt)
	{
		position += velocity * dt;
		velocity += acceleration * dt;
	}

}