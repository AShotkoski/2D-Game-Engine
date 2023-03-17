#include "Drawable.h"
#include <Binds/Bindable.h>
#include <Util/MathUtil.h>
#include <Binds/Topology.h>
#include <Binds/PixelShader.h>
#include <Binds/VertexShader.h>
#include <Binds/InputLayout.h>

Drawable::Drawable( Graphics& gfx ) 
	: CBData{  DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity()), gfx.camera.GetMatrix() }
{
	pTransformCB = std::make_unique<Binds::VertexConstantBuffer<ConstBuffer>>( gfx,CBData, 0u );
	AddBind( std::make_unique<Binds::Topology>( gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) );
	AddBind( std::make_unique<Binds::PixelShader>( gfx, L"SolidPS.cso" ) );
	auto vs = std::make_unique<Binds::VertexShader>( gfx, L"TransformVS.cso" );
	auto vsByteCode = vs->pGetBytecode();
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputDesc;
	inputDesc.push_back( { "POSITION", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u } );
	AddBind( std::make_unique <Binds::InputLayout>( gfx, std::move( inputDesc ), *vsByteCode ) );
	AddBind( std::move( vs ) );
}

void Drawable::AddBind( std::unique_ptr<Bindable> bind )
{
	BindPtrs.push_back( std::move( bind ) );
}

void Drawable::BindAll( Graphics& gfx ) const
{
	for ( auto& b : BindPtrs )
	{
		b->Bind( gfx );
	}
	pTransformCB->Bind( gfx );
}

void Drawable::UpdateTransformBuffer(Graphics& gfx)
{
	using namespace DirectX;
	auto vecpos = XMVectorSet( Position.x, Position.y, 0, 0 );
	CBData.model = XMMatrixTranspose( XMMatrixTranslationFromVector( vecpos ) );
	CBData.view = gfx.camera.GetMatrix();
	pTransformCB->Update( gfx, CBData );
}
