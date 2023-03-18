#include "Renderer.h"
#include <Draw/Drawable.h>

void Renderer::RegisterDrawable( std::unique_ptr<Drawable> drawable )
{
	drawablePtrs.push_back( std::move( drawable ) );
}

void Renderer::Execute( Graphics& gfx )
{
	for ( auto& d : drawablePtrs )
	{
		d->Draw( gfx );
	}
}
