#pragma once
#include "Vec2.h"

namespace Phys
{
	class RigidBody
	{
		friend class System;
	public:
		RigidBody(Vec2* pPos, float m, Vec2 v, Vec2 a);
		void UpdatePtrs(Vec2* pPos);
	private:
		void Process(float dt);
	private:
		Vec2* pPosition = nullptr;
		float mass;
		Vec2 velocity;
		Vec2 acceleration;
	};

}
