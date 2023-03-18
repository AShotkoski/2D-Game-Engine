#include "BaseEntity.h"
#include <log.h>
#include <Render/Renderer.h>
#include <Draw/Drawable.h>

BaseEntity::BaseEntity( Graphics& gfx, std::unique_ptr<Drawable> model,
						Vec2 pos, float width, float height, float rotation)
	: position(pos)
	, width(width)
	, height(height)
	, rotation(rotation)
{
	DCHECK_F( (bool)model, "invalid model on creation of base entity" );

	pModel = model.get();
	gfx.renderer.RegisterDrawable( std::move( model ) );
	pModel->UpdateTransformBuffer( position, rotation, width, height, gfx );
}
