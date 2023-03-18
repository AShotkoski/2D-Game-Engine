#include "Game.h"
#include "Util/Colors.h"
#include "Util/MathUtil.h"
#include "Util/Point.h"
#include <numbers>

namespace dx = DirectX;

Game::Game()
	: wnd( ScreenWidth, ScreenHeight, WindowTitle )
	, gfx( wnd.GFX() )
	, plane( gfx, Rect::Make({0,0 },5.f,0.1f))
	, circle( gfx, { 2.f, 1.6f }, 0.3f, 20  )
{
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
			if ( e->GetVirtualKey() == 'E' )
			{
				pointDrawer.AddPoint( { 0.5f,0.5f }, Colors::OrangeRed, gfx );
			}
			if ( e->GetVirtualKey() == 'R' )
			{
				pointDrawer.AddPoint( { -0.5f,-0.5f }, Colors::Blue, gfx );
			}

		}
	}

	if ( wnd.kbd.KeyIsPressed( 'I' ) )
	{
		gfx.camera.UpdatePosition( {0, 1.f }, dt);
	}
	else if ( wnd.kbd.KeyIsPressed( 'K' ) )
	{
		gfx.camera.UpdatePosition( {0, -1.f }, dt);
	}
	else if ( wnd.kbd.KeyIsPressed( 'J' ) )
	{
		gfx.camera.UpdatePosition( {-1.f, 0 }, dt);
	}
	else if ( wnd.kbd.KeyIsPressed( 'L' ) )
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
}

void Game::DrawFrame()
{
	pointDrawer.Draw( gfx );
	plane.Draw( gfx );
	circle.Draw( gfx );
}
