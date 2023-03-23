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
	for ( size_t i = 0; i < 100; i++ )
	{
		auto randvec = Vec2{ NumberFactory::RandomReal( -100.f,100.f ),NumberFactory::RandomReal( -2.f,100.f ) };
		balls.emplace_back( gfx, &physicsScene ,randvec, NumberFactory::RandomReal(0.1f, 2.f) );
	}
	DLOG_F( INFO, "created" );
}

Game::~Game()
{
}

void Game::Go()
{
	//LOG_SCOPE_F( INFO, "go");
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
	//LOG_SCOPE_F( INFO, "updatelogic" );
	while ( auto e = wnd.kbd.GetEvent() )
	{
		if ( e->GetType() == Keyboard::Event::Keydown )
		{
			if ( e->GetVirtualKey() == 'G' )
			{
				//balls[0].ApplyImpl(Vec2{ 0.001f,9.8f });
				while (!balls.empty())
					balls.pop_back();
			}
		}
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
