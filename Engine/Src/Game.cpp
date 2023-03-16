#include "Game.h"
#include "Util/Colors.h"
#include "Util/MathUtil.h"
#include "Util/Point.h"
#include <numbers>

namespace dx = DirectX;

Game::Game()
	: wnd( ScreenWidth, ScreenHeight, WindowTitle )
	, gfx( wnd.GFX() )
	, plane( gfx, { 0.25f,0 }, 0.1f )
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
			if ( e->GetVirtualKey() == 'A' )
			{
				pointDrawer.AddPoint( { 0.5f,0.5f }, gfx );
			}
			if ( e->GetVirtualKey() == 'S' )
			{
				pointDrawer.AddPoint( { -0.5f,-0.5f }, gfx );
			}
		}
	}
	
}

void Game::DrawFrame()
{
	pointDrawer.Draw( gfx );
	plane.Draw( gfx );
}
