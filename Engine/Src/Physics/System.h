#pragma once

#include <memory>
#include <vector>

namespace Phys
{
	class RigidBody;

	class System
	{
	public:
		virtual ~System() = default;
		System() = default;

		float GetGravity() const;
		void SetGravity(float g);

		void RegisterRigidBody(RigidBody* body);
		void UnregisterRigidBody(RigidBody* body);

		void Process(float dt, size_t iterations = 1);
	private:
		std::vector<RigidBody* > RigidBodies;
	private:
		float gravity = -9.81f; // m * s^-2
	};
}