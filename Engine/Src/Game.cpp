#include "Game.h"
#include "Util/Colors.h"
#include "Util/MathUtil.h"
#include <numbers>
#include "Binds/IndexBuffer.h"
#include "Binds/InputLayout.h"
#include "Binds/PixelShader.h"
#include "Binds/RenderTarget.h"
#include "Binds/Topology.h"
#include "Binds/VertexBuffer.h"
#include "Binds/VertexShader.h"

namespace dx = DirectX;

Game::Game()
	: wnd( ScreenWidth, ScreenHeight, WindowTitle )
	, gfx( wnd.GFX() )
{
	binds.push_back( std::make_unique<Binds::Topology>( gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) );
	binds.push_back( std::make_unique<Binds::PixelShader>( gfx, L"PixelShader.cso" ) );
	auto vs = std::make_unique<Binds::VertexShader>( gfx, L"VertexShader.cso" );
	auto vsByteCode = vs->pGetBytecode();
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputDesc;
	inputDesc.push_back( { "POSITION", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0u } );
	binds.push_back( std::make_unique <Binds::InputLayout>( gfx, std::move( inputDesc ), *vsByteCode ) );
	binds.push_back( std::move( vs ) );
	struct vertex
	{
		float x, y;
	};
	std::vector<vertex> vb;
	vb.emplace_back( 0.f, 0.5f );
	vb.emplace_back( 0.5f, 0.f );
	vb.emplace_back( -0.5f, 0.f );
	std::vector<unsigned short> ib = { 0,1,2 };
	binds.push_back( std::make_unique<Binds::VertexBuffer>( gfx, vb ) );
	binds.push_back( std::make_unique<Binds::IndexBuffer>( gfx, ib ) );
}

Game::~Game()
{
}

void Game::Go()
{
	// Capture frame time
	dt = ft.Mark();
	adj_dt = dt * timeFactor;

	gfx.BeginFrame();
	UpdateLogic();
	DrawFrame();

	gfx.EndFrame();
}

void Game::UpdateLogic()
{		
	for ( auto& b : binds )
	{
		b->Bind( gfx );
	}
	gfx.DrawIndexed( 3u );
}

void Game::DrawFrame()
{
}
