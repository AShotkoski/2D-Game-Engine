#pragma once
#include "BaseEntity.h"

class Graphics;
class Drawable;
namespace Phys
{
	class RigidBody;
	class System;
}

class RigidBodyEntity : public BaseEntity
{
protected:
	RigidBodyEntity(
		Graphics&                        gfx,
		Phys::System*                    scene,
		std::shared_ptr<Drawable>        model,
		Vec2                             pos,
		float mass,
		float                            width    = 1.f,
		float                            height   = 1.f,
		float                            rotation = 0.f );
	~RigidBodyEntity() noexcept;
	RigidBodyEntity(const RigidBodyEntity& src) = delete;
	RigidBodyEntity(RigidBodyEntity&& src);
private:
	Phys::System*& pPhysicsScene;
	std::shared_ptr<Phys::RigidBody> body;
};