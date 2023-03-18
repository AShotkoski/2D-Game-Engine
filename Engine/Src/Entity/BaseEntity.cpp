#include "BaseEntity.h"
#include <log.h>
#include <Render/Renderer.h>
#include <Draw/Drawable.h>

BaseEntity::BaseEntity( Renderer& Renderer, std::unique_ptr<Drawable> model )
{
	DCHECK_F( (bool)model, "invalid model on creation of base entity" );

	Renderer.RegisterDrawable( std::move( model ) );
}
