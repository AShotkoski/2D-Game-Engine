#include "Circle.h"
#include <Binds/Topology.h>
#include <Binds/VertexBuffer.h>
#include <Binds/IndexBuffer.h>

Circle::Circle( Graphics& gfx, size_t resolution )
	: Drawable(gfx)
{
	AddBind( Binds::Topology::Resolve( gfx, D3D11_PRIMITIVE_TOPOLOGY_LINELIST ) );
	std::vector<Vec2> verts;
	std::vector<unsigned short> inds;
	// Generate circle
	constexpr float pi = 3.1415926f;
	const float step = ( 2.f * pi ) / float( resolution );
	for ( size_t i = 0; i < resolution; i++ )
	{
		const float ang = i * step;
		verts.emplace_back( (float)cos( ang ), (float)sin( ang ) );

		inds.push_back( (unsigned short)i );
		inds.push_back( (unsigned short)(i == resolution - 1 ? 0 : i + 1) );
	}
	AddBind( Binds::VertexBuffer::Resolve( gfx, verts, "Circle"));
	AddBind( Binds::IndexBuffer::Resolve( gfx, inds, "Circle"));
	SetIndicesCount((UINT)inds.size());
}
