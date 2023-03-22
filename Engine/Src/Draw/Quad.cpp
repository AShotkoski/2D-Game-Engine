#include "Quad.h"
#include "Binds/InputLayout.h"
#include "Binds/PixelShader.h"
#include "Binds/RenderTarget.h"
#include "Binds/Topology.h"
#include "Binds/VertexBuffer.h"
#include "Binds/IndexBuffer.h"
#include "Binds/VertexShader.h"

Quad::Quad( Graphics& gfx )
	: Drawable(gfx)
{
	// Make vertices
	std::vector<Vec2> verts;
	verts.emplace_back( -1.f, 1.f );
	verts.emplace_back(  1.f, 1.f  );
	verts.emplace_back(  1.f, -1.f  );
	verts.emplace_back(  -1.f, -1.f  );
	AddBind( Binds::VertexBuffer::Resolve( gfx, verts, "Quad"));
	std::vector<unsigned short> inds = { 0,1,2,0,2,3 };
	AddBind( Binds::IndexBuffer::Resolve( gfx, inds, "Quad"));
	AddBind( Binds::Topology::Resolve( gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) );
	SetIndicesCount((UINT)inds.size());
}