#pragma once
#include <vector>
#include <memory>

class Drawable;
class Graphics;

class Renderer
{
public:
	Renderer() = default;
	void RegisterDrawable(Drawable* pDrawable );
	void UnregisterDrawable( const Drawable* pDrawable );
	void Execute( Graphics& gfx ) const;
private:
	std::vector<Drawable*> drawablePtrs;
};