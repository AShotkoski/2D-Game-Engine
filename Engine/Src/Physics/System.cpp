#include "System.h"
#include <Entity/RigidBodyEntity.h>
#include "RigidBody.h"
#include <log.h>
#include <algorithm>

namespace Phys
{
	float System::GetGravity() const
	{
		return gravity;
	}
	void System::SetGravity(float g)
	{
		gravity = g;
	}
	size_t System::RegisterRigidBodyEntity(RigidBodyEntity* ent)
	{
		DCHECK_NOTNULL_F(ent, "invalid rigid body registration.");
		RigidBodyEntities.push_back(std::move(ent));
		return RigidBodyEntities.size() - 1;
	}
	void System::UnregisterRigidBodyEntity(RigidBodyEntity* ent)
	{
		//std::erase_if(RigidBodies,
		//	[body](const RigidBody* d) { return d == body; });
	}

	void System::UpdateRigidBodyEntityPtr(RigidBodyEntity* newent, size_t idx)
	{
		DCHECK_F(idx < RigidBodyEntities.size(), "incorrect index to rigid body");
		DCHECK_NOTNULL_F(newent, "new ent cannot be null");
		RigidBodyEntities[idx] = newent;
	}

	void System::Process(float dt, size_t iterations)
	{
		DCHECK_F(iterations > 0, "Cannot have 0 iterations");
		dt = dt / iterations; // Subdivide time by number of iterations

		// Having the policy be a lambda gives us the option to add an overload of process        
		// that could inject its own policy in the future. (and we get to use for_each)
		//const auto policy = [this, dt](std::shared_ptr<RigidBody>& body)
		//{
			//body->acceleration += this->GetGravity();
			//body->Process(dt);
		//};
		for (size_t i = 0; i < iterations; i++)
		{
			//std::for_each(RigidBodies.begin(), RigidBodies.end(), policy);
			for (auto& e : RigidBodyEntities)
			{
				e->pGetBody()->Process(dt);
				e->UpdateModel();
			}
		}
	}
}
