#include "Renderer.h"
#include <Draw/Drawable.h>
#include <log.h>

void Renderer::RegisterDrawable( std::shared_ptr<Drawable> drawable )
{
	drawablePtrs.push_back( std::move( drawable ) );
}

void Renderer::DestroyDrawable( Drawable* pDrawable )
{
	std::erase_if( drawablePtrs,
					[pDrawable]( std::shared_ptr<Drawable>& d ) { return d.get() == pDrawable; } );
}

void Renderer::Execute( Graphics& gfx ) const
{
	for ( auto& d : drawablePtrs )
	{
		d->Draw( gfx );
	}
}
