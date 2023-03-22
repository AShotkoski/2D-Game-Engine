#pragma once
#include <vector>
#include <memory>

class Drawable;
class Graphics;

class Renderer
{
public:
	Renderer() = default;
	void RegisterDrawable(std::shared_ptr<Drawable> pDrawable );
	void DestroyDrawable( const Drawable* pDrawable );
	void Execute( Graphics& gfx ) const;
private:
	std::vector<std::shared_ptr<Drawable>> drawables;
};