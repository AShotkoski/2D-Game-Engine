#include "Game.h"
#include "Util/Colors.h"
#include "Util/MathUtil.h"
#include <numbers>

namespace dx = DirectX;

Game::Game()
	: wnd( ScreenWidth, ScreenHeight, WindowTitle )
	, gfx( wnd.GFX() )
	, ball( gfx, { 0.f, 5.f }, 0.75f  )
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
	gfx.ExecuteRenderer();
}
