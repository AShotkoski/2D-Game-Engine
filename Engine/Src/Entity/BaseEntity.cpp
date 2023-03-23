#include "BaseEntity.h"
#include <log.h>
#include <Render/Renderer.h>
#include <Draw/Drawable.h>
#include <Physics/RigidBody.h>

BaseEntity::BaseEntity( Graphics& gfx, std::unique_ptr<Drawable> model,
						Vec2 pos, float width, float height, float rotation)
	: position(pos)
	, width(width)
	, height(height)
	, rotation(rotation)
	, gfx(gfx)
	, pModel(std::move(model))
{
	DCHECK_F( (bool)pModel, "invalid model on creation of base entity" );

	gfx.renderer.RegisterDrawable(  pModel.get()  );
	pModel->UpdateTransformBuffer( position, rotation, width, height, gfx );
}

BaseEntity::BaseEntity(BaseEntity&& src) noexcept
	: gfx(src.gfx)
	, position(src.position)
	, rotation(src.rotation)
	, width(src.width)
	, height(src.height)
	, pModel(std::move(src.pModel))
{
}

void BaseEntity::UpdateModel() const
{
	pModel->UpdateTransformBuffer( position, rotation, width, height, gfx );
}

BaseEntity::~BaseEntity() noexcept
{
	if (pModel)
	{
		gfx.renderer.UnregisterDrawable(pModel.get());
	}
}
