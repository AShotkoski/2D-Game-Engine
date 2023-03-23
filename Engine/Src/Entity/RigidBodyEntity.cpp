#include "RigidBodyEntity.h"
#include <Physics/System.h>
#include <Physics/RigidBody.h>
#include <Draw/Drawable.h>
#include <log.h>

Phys::RigidBody* RigidBodyEntity::pGetBody()
{
	return body.get();
}

RigidBodyEntity::RigidBodyEntity(
	Graphics&                        gfx,
	Phys::System*                    scene,
	std::unique_ptr<Drawable>        model,
	Vec2                             pos,
	float mass,
	float                            width,
	float                            height,
	float                            rotation )
	: BaseEntity(gfx, std::move(model), pos, width, height, rotation)
	, pPhysicsScene(scene)
	, body(std::make_unique<Phys::RigidBody>( &position, mass, Vec2{ 0,0 }, Vec2{ 0,0 }))
{
	DCHECK_F((bool)body, "Null body in creation of rigid body entity");
	DCHECK_NOTNULL_F(scene, "null scene in creation of rigid body entity");

	sceneIdx = scene->RegisterRigidBodyEntity(this);
}

RigidBodyEntity::~RigidBodyEntity() noexcept
{
	if (body)
	{
		pPhysicsScene->UnregisterRigidBodyEntity(this);
	}
}

RigidBodyEntity::RigidBodyEntity(RigidBodyEntity&& src) noexcept
	: BaseEntity(std::move(src))
	, pPhysicsScene(src.pPhysicsScene)
	, body(std::move(src.body))
	, sceneIdx(std::move(src.sceneIdx))
{
	body->UpdatePtrs(&position);
	pPhysicsScene->UpdateRigidBodyEntityPtr(this, sceneIdx);
}
