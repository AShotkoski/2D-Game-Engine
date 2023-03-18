#pragma once
#include <vector>
#include <memory>

class Drawable;
class Graphics;

class Renderer
{
public:
	Renderer() = default;
	void RegisterDrawable( std::unique_ptr<Drawable> drawable );
	void Execute( Graphics& gfx ) const;
private:
	std::vector<std::unique_ptr<Drawable>> drawablePtrs;
};