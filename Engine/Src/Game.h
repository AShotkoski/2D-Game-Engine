#pragma once
#include "Core/Window.h"
#include "Util/FrameTimer.h"
#include <Physics/System.h>
#include <Entity/Ball.h>

class Game
{
public:
	Game();
	~Game();
	Game( const Game& ) = delete;
	const Game& operator=( const Game& ) = delete;
	void Go();
private:
	void UpdateLogic();
	void DrawFrame();
private:
	Window wnd;
	Graphics& gfx;
	FrameTimer ft;
	Phys::System physicsScene;
private:
	float dt = 0.f;
	float adj_dt = 0.f;
	float timeFactor = 1.f;
	std::vector<Ball> balls;
private:
	static constexpr UINT ScreenWidth = 1272u;
	static constexpr UINT ScreenHeight = 954u;
	static constexpr const wchar_t* WindowTitle = L"2D bruh";
};

