#pragma once

#include <memory>
#include <vector>

class RigidBodyEntity;

namespace Phys
{

	class System
	{
	public:
		virtual ~System() = default;
		System() = default;

		float GetGravity() const;
		void SetGravity(float g);

		size_t RegisterRigidBodyEntity(RigidBodyEntity* ent);
		void UnregisterRigidBodyEntity(RigidBodyEntity* ent);
		void UpdateRigidBodyEntityPtr(RigidBodyEntity* newent, size_t idx);

		void Process(float dt, size_t iterations = 1);
	private:
		std::vector<RigidBodyEntity* > RigidBodyEntities;
	private:
		float gravity = -9.81f; // m * s^-2
	};
}