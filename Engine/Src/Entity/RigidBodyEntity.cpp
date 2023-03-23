#include "RigidBodyEntity.h"
#include <Physics/System.h>
#include <Physics/RigidBody.h>
#include <log.h>

RigidBodyEntity::RigidBodyEntity(
	Graphics&                        gfx,
	Phys::System*                    scene,
	std::shared_ptr<Drawable>        model,
	Vec2                             pos,
	float mass,
	float                            width,
	float                            height,
	float                            rotation )
	: BaseEntity(gfx, std::move(model), pos, width, height, rotation)
	, pPhysicsScene(scene)
	, body(std::make_shared<Phys::RigidBody>(mass, position, Vec2{ 0,0 }, Vec2{ 0,0 }))
{
	DCHECK_F((bool)body, "Null body in creation of rigid body entity");
	DCHECK_NOTNULL_F(scene, "null scene in creation of rigid body entity");

	scene->RegisterRigidBody(std::ref(body));
}

RigidBodyEntity::~RigidBodyEntity() noexcept
{
	if (body)
	{
		pPhysicsScene->UnregisterRigidBody(body.get());
	}
}

RigidBodyEntity::RigidBodyEntity(RigidBodyEntity&& src)
	: BaseEntity(std::move(src))
	, pPhysicsScene(src.pPhysicsScene)
	, body(std::move(src.body))
{
}
