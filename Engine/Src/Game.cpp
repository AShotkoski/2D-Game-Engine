#include "Game.h"
#include "Util/Colors.h"
#include "Util/MathUtil.h"
#include <numbers>
#include <log.h>
#include <Util/NumberFactory.h>

namespace dx = DirectX;

Game::Game()
	: wnd( ScreenWidth, ScreenHeight, WindowTitle )
	, gfx( wnd.GFX() )
{
	for ( size_t i = 0; i < 1000; i++ )
	{
		auto randvec = Vec2{ NumberFactory::RandomReal( -10.f,10.f ),NumberFactory::RandomReal( -2.f,10.f ) };
		balls.emplace_back( gfx, randvec, NumberFactory::RandomReal(0.1f, 2.f) );
	}
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
	while ( auto e = wnd.kbd.GetEvent() )
	{
		if ( e->GetType() == Keyboard::Event::Keydown )
		{
			if ( e->GetVirtualKey() == 'G' )
			{
				balls[0].ApplyImpl(Vec2{ 0.001f,9.8f });
			}
		}
	}
	if ( wnd.kbd.KeyIsPressed( 'N' ) )
	{
		balls.emplace_back( gfx, Vec2{ NumberFactory::RandomReal( -10.f,10.f ), NumberFactory::RandomReal( -2.f,10.f ) }, NumberFactory::RandomReal( 0.1f, 1.2f ) );
		balls.emplace_back( gfx, Vec2{ NumberFactory::RandomReal( -10.f,10.f ), NumberFactory::RandomReal( -2.f,10.f ) }, NumberFactory::RandomReal( 0.1f, 1.2f ) );
		balls.emplace_back( gfx, Vec2{ NumberFactory::RandomReal( -10.f,10.f ), NumberFactory::RandomReal( -2.f,10.f ) }, NumberFactory::RandomReal( 0.1f, 1.2f ) );
		balls.emplace_back( gfx, Vec2{ NumberFactory::RandomReal( -10.f,10.f ), NumberFactory::RandomReal( -2.f,10.f ) }, NumberFactory::RandomReal( 0.1f, 1.2f ) );
		balls.emplace_back( gfx, Vec2{ NumberFactory::RandomReal( -10.f,10.f ), NumberFactory::RandomReal( -2.f,10.f ) }, NumberFactory::RandomReal( 0.1f, 1.2f ) );
	}

	if ( wnd.kbd.KeyIsPressed( 'W' ) )
	{
		gfx.camera.UpdatePosition( {0, 1.f }, dt);
	}
	else if ( wnd.kbd.KeyIsPressed( 'S' ) )
	{
		gfx.camera.UpdatePosition( {0, -1.f }, dt);
	}
	else if ( wnd.kbd.KeyIsPressed( 'A' ) )
	{
		gfx.camera.UpdatePosition( {-1.f, 0 }, dt);
	}
	else if ( wnd.kbd.KeyIsPressed( 'D' ) )
	{
		gfx.camera.UpdatePosition( {1.f, 0 }, dt);
	}
	while ( auto e = wnd.mouse.GetEvent() )
	{
		if ( e->GetType() == Mouse::Event::ScrollDown )
		{
			gfx.camera.UpdateZoom( -0.1f );
		}
		else if ( e->GetType() == Mouse::Event::ScrollUp )
		{
			gfx.camera.UpdateZoom( 0.1f );
		}
	}

	for ( auto& b : balls )
	{
		b.Update( adj_dt );
	}
}

void Game::DrawFrame()
{
	gfx.ExecuteRenderer();
}
