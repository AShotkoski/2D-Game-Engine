#pragma once
#include <vector>
#include <memory>

class Drawable;
class Graphics;

class Renderer
{
public:
	Renderer() = default;
	void RegisterDrawable( std::shared_ptr<Drawable> drawable );
	void DestroyDrawable( Drawable* pDrawable );
	void Execute( Graphics& gfx ) const;
private:
	std::vector<std::shared_ptr<Drawable>> drawablePtrs;
};