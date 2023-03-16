#include "PointDrawer.h"
#include "Binds/InputLayout.h"
#include "Binds/PixelShader.h"
#include "Binds/RenderTarget.h"
#include "Binds/Topology.h"
#include "Binds/VertexBuffer.h"
#include "Binds/VertexShader.h"
#include <Util/Point.h>
#include <Util/Colors.h>

bool PointDrawer::Empty() const
{
	return points.empty() && BindPtrs.empty();
}

void PointDrawer::AddPoint( Point pt, Graphics& gfx )
{
	if ( Empty() )
	{
		points.push_back( std::move( pt ) );
		_Init(gfx);
	}
	else
	{
		_AddPoint( std::move(pt), gfx );
	}
}

void PointDrawer::Draw( Graphics& gfx ) const
{
	if ( Empty() )
		return;
	for ( const auto& b : BindPtrs )
	{
		b->Bind( gfx );
	}
	pVertexBuffer->Bind( gfx );
	gfx.Draw( (UINT)points.size(), 0u );
}

void PointDrawer::_Init(Graphics& gfx)
{
	BindPtrs.push_back( std::make_unique<Binds::Topology>( gfx, D3D11_PRIMITIVE_TOPOLOGY_POINTLIST ) );
	BindPtrs.push_back( std::make_unique<Binds::PixelShader>( gfx, L"PixelShader.cso" ) );
	auto vs = std::make_unique<Binds::VertexShader>( gfx, L"VertexShader.cso" );
	auto vsByteCode = vs->pGetBytecode();
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputDesc;
	inputDesc.push_back( { "POSITION", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u } );
	BindPtrs.push_back( std::make_unique <Binds::InputLayout>( gfx, std::move( inputDesc ), *vsByteCode ) );
	BindPtrs.push_back( std::move( vs ) );

	pVertexBuffer = std::make_unique<Binds::VertexBuffer>( gfx, points );
}

void PointDrawer::_AddPoint( Point pt, Graphics& gfx )
{
	points.push_back( std::move( pt ) );
	auto old = pVertexBuffer.release();
	delete old;
	pVertexBuffer = std::make_unique<Binds::VertexBuffer>( gfx, points );
}
