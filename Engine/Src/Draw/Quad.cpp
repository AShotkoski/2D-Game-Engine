#include "Quad.h"
#include <Util/Point.h>
#include "Binds/InputLayout.h"
#include "Binds/PixelShader.h"
#include "Binds/RenderTarget.h"
#include "Binds/Topology.h"
#include "Binds/VertexBuffer.h"
#include "Binds/IndexBuffer.h"
#include "Binds/VertexShader.h"

Quad::Quad( Graphics& gfx, Point center, float size )
	: Drawable(gfx)
{
	AddBind( std::make_unique<Binds::Topology>( gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) );
	AddBind( std::make_unique<Binds::PixelShader>( gfx, L"PixelShader.cso"));
	auto vs = std::make_unique<Binds::VertexShader>( gfx, L"VertexShader.cso" );
	auto vsByteCode = vs->pGetBytecode();
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputDesc;
	inputDesc.push_back( { "POSITION", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u } );
	AddBind( std::make_unique <Binds::InputLayout>( gfx, std::move( inputDesc ), *vsByteCode ) );
	AddBind( std::move( vs ) );
	// Make vertices
	std::vector<Point> verts;
	verts.emplace_back( center + Point{-size, size} );
	verts.emplace_back( center + Point{size, size} );
	verts.emplace_back( center + Point{size, -size} );
	verts.emplace_back( center + Point{-size, -size} );
	AddBind( std::make_unique<Binds::VertexBuffer>( gfx, verts ) );
	std::vector<unsigned short> inds = { 0,1,2,0,2,3 };
	AddBind( std::make_unique<Binds::IndexBuffer>( gfx, inds ) );
	idxCount = (UINT)inds.size();
}

void Quad::Draw( Graphics& gfx ) const
{
	BindAll( gfx );
	gfx.DrawIndexed( idxCount );
}
