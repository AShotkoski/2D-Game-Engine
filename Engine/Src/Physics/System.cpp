#include "System.h"
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
	void System::RegisterRigidBody(RigidBody* body)
	{
		DCHECK_NOTNULL_F(body, "invalid rigid body registration.");
		RigidBodies.push_back(std::move(body));
	}
	void System::UnregisterRigidBody(RigidBody* body)
	{
		std::erase_if(RigidBodies,
			[body](const RigidBody* d) { return d == body; });
	}
	void System::Process(float dt, size_t iterations)
	{
		DCHECK_F(iterations > 0, "Cannot have 0 iterations");
		dt = dt / iterations; // Subdivide time by number of iterations

		// Having the policy be a lambda gives us the option to add an overload of process        
		// that could inject its own policy in the future. (and we get to use for_each)
		const auto policy = [this, dt](std::shared_ptr<RigidBody>& body)
		{
			body->acceleration += this->GetGravity();
			body->Process(dt);
		};
		for (size_t i = 0; i < iterations; i++)
		{
			//std::for_each(RigidBodies.begin(), RigidBodies.end(), policy);
			for (auto& b : RigidBodies)
			{
				b->Process(dt);
				
			}
		}
	}
}
