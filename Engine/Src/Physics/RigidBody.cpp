#include "RigidBody.h"
#include <log.h>

namespace Phys
{
	RigidBody::RigidBody(Vec2* pPos, float m, Vec2 v, Vec2 a)
		:  velocity(v)
		, acceleration(a)
		, mass(m)
		, pPosition(pPos)
	{
		DCHECK_NOTNULL_F(pPos, "Invalid position in creationo of rigidbody");
	}
	void RigidBody::Process(float dt)
	{
		DCHECK_NOTNULL_F(pPosition, "position null :(");
		acceleration.y = -9.81f;//
		velocity += acceleration * dt;
		if (pPosition->y <= -10.f)
			velocity = 0;
		*pPosition += velocity * dt;
	}

}