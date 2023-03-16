#include "Topology.h"
#include <typeinfo>

namespace Binds
{

	Topology::Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type )
		:
		type( type )
	{}

	void Topology::Bind( Graphics& gfx )
	{
		pGetContext( gfx )->IASetPrimitiveTopology( type );
	}


};