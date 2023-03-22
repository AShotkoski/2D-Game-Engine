#include "Renderer.h"
#include <Draw/Drawable.h>
#include <log.h>

void Renderer::RegisterDrawable(std::shared_ptr<Drawable> pDrawable )
{
	drawables.push_back( std::move(pDrawable) );
}

void Renderer::DestroyDrawable( const Drawable* pDrawable )
{
	std::erase_if( drawables,
					[pDrawable](const std::shared_ptr<Drawable>& d ) { return d.get() == pDrawable; });
}

void Renderer::Execute( Graphics& gfx ) const
{
	for ( auto& d : drawables )
	{
		d->BindAll( gfx );
		gfx.DrawIndexed(d->GetIndicesCount());
	}
}
