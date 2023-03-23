#pragma once
#include "Vec2.h"

namespace Phys
{
	class RigidBody
	{
		friend class System;
	public:
		RigidBody(float m, Vec2& pos, Vec2 v, Vec2 a);
	private:
		void Process(float dt);
	private:
		// The vars that are refs are because the base entity that owns this rigidbody
		// is what owns the data for it and it is likely shared with other classes
		// that use the entity.
		float mass;
		Vec2& position;
		Vec2 velocity;
		Vec2 acceleration;
	};

}
