#include "Renderer.h"
#include <Draw/Drawable.h>
#include <log.h>

void Renderer::RegisterDrawable(Drawable* pDrawable )
{
	DCHECK_NOTNULL_F(pDrawable, "Drawable cannot be null");
	drawablePtrs.push_back( std::move(pDrawable) );
}

void Renderer::UnregisterDrawable( const Drawable* pDrawable )
{
	std::erase_if(drawablePtrs,
					[pDrawable](const Drawable* d ) { return d == pDrawable; });
}

void Renderer::Execute( Graphics& gfx ) const
{
	for ( auto& d : drawablePtrs )
	{
		d->BindAll( gfx );
		gfx.DrawIndexed(d->GetIndicesCount());
	}
}
