#include "Drawable.h"
#include <Binds/Bindable.h>
#include <Util/MathUtil.h>
#include <Binds/Topology.h>
#include <Binds/PixelShader.h>
#include <Binds/VertexShader.h>
#include <Binds/InputLayout.h>
#include <log.h>

UINT Drawable::GetIndicesCount() const
{
	DCHECK_F(IndicesCount > 0u, "You must set indices count before calling getindicescount.");
	return IndicesCount;
}

Drawable::Drawable( Graphics& gfx )
	: CBData{  DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity()), gfx.camera.GetMatrixWithProjection() }
{
	pTransformCB = std::make_unique<Binds::VertexConstantBuffer<ConstBuffer>>( gfx,CBData, 0u );
	AddBind( Binds::PixelShader::Resolve( gfx, L"SolidPS.cso" ) );
	auto vs = Binds::VertexShader::Resolve( gfx, L"TransformVS.cso" );
	auto vsByteCode = vs->pGetBytecode();
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputDesc;
	inputDesc.push_back( { "POSITION", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u } );
	AddBind( Binds::InputLayout::Resolve( gfx, std::move( inputDesc ), *vsByteCode ) );
	AddBind( std::move( vs ) );
}

void Drawable::AddBind( std::shared_ptr<Bindable> bind )
{
	BindPtrs.push_back( std::move( bind ) );
}

void Drawable::BindAll( Graphics& gfx ) const
{
	if ( gfx.camera.isDirty() )
		const_cast<Drawable*>(this)->UpdateTransformBufferCamera( gfx );
	for ( auto& b : BindPtrs )
	{
		b->Bind( gfx );
	}
	pTransformCB->Bind( gfx );
}

void Drawable::UpdateTransformBuffer( Vec2 pos, float theta, float width, float height, Graphics& gfx )
{
	using namespace DirectX;
	auto vecpos = XMVectorSet( pos.x, pos.y, 0, 0 );
	CBData.model = XMMatrixTranspose( XMMatrixScaling(width,height,1.f) *
									  XMMatrixRotationRollPitchYaw(0.f, 0.f, theta) *
									  XMMatrixTranslationFromVector( vecpos ) );
	CBData.viewproj = XMMatrixTranspose( gfx.camera.GetMatrixWithProjection());
	pTransformCB->Update( gfx, CBData );
}

void Drawable::UpdateTransformBufferCamera(Graphics& gfx )
{
	using namespace DirectX;
	CBData.viewproj = XMMatrixTranspose( gfx.camera.GetMatrixWithProjection());
	pTransformCB->Update( gfx, CBData );
}

void Drawable::SetIndicesCount(UINT count)
{
	DCHECK_F(count > 0u, "Cannot set a drawable to have 0 indices.");
	IndicesCount = count;
}
