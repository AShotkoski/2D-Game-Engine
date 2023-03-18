#include "Circle.h"
#include <Binds/Topology.h>
#include <Binds/VertexBuffer.h>
#include <Binds/IndexBuffer.h>

Circle::Circle( Graphics& gfx, Point pos, float radius )
	: Drawable(gfx)
	, radius(radius)
{
	Position = pos;
	ScaleWidth = ScaleHeight = radius;

	AddBind( std::make_unique<Binds::Topology>( gfx, D3D11_PRIMITIVE_TOPOLOGY_LINELIST ) );
	std::vector<Point> verts;
	std::vector<unsigned short> inds;
	// Generate circle
	constexpr size_t resolution = 10;
	constexpr float pi = 3.1415926f;
	const float step = ( 2.f * pi ) / float( resolution );
	for ( size_t i = 0; i < resolution; i++ )
	{
		const float ang = i * step;
		verts.emplace_back( (float)cos( ang ), (float)sin( ang ) );

		inds.push_back( (unsigned short)i );
		inds.push_back( (unsigned short)(i == resolution - 1 ? 0 : i + 1) );
	}
	AddBind( std::make_unique<Binds::VertexBuffer>( gfx, verts ) );
	AddBind( std::make_unique<Binds::IndexBuffer>( gfx, inds ) );
	idxCount = (UINT)inds.size();
}

void Circle::Draw( Graphics& gfx ) const
{
	BindAll( gfx );
	gfx.DrawIndexed( idxCount );
}
