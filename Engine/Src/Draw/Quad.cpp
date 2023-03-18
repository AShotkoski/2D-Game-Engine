#include "Quad.h"
#include <Util/Point.h>
#include "Binds/InputLayout.h"
#include "Binds/PixelShader.h"
#include "Binds/RenderTarget.h"
#include "Binds/Topology.h"
#include "Binds/VertexBuffer.h"
#include "Binds/IndexBuffer.h"
#include "Binds/VertexShader.h"

Quad::Quad( Graphics& gfx, Rect rect )
	: Drawable(gfx)
{
	Position = rect.GetCenter();
	ScaleWidth = rect.GetWidth();
	ScaleHeight = rect.GetHeight();
	// Make vertices
	std::vector<Point> verts;
	verts.emplace_back( -1.f, 1.f );
	verts.emplace_back(  1.f, 1.f  );
	verts.emplace_back(  1.f, -1.f  );
	verts.emplace_back(  -1.f, -1.f  );
	AddBind( std::make_unique<Binds::VertexBuffer>( gfx, verts ) );
	std::vector<unsigned short> inds = { 0,1,2,0,2,3 };
	AddBind( std::make_unique<Binds::IndexBuffer>( gfx, inds ) );
	idxCount = (UINT)inds.size();
	AddBind( std::make_unique<Binds::Topology>( gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) );
}

void Quad::Draw( Graphics& gfx ) const
{
	BindAll( gfx );
	gfx.DrawIndexed( idxCount );
}
