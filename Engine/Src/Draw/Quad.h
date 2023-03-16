#pragma once
#include "Drawable.h"

class Point;

class Quad : public Drawable
{
public:
	// todo make it not be a square lmao
	Quad( Graphics& gfx, Point center, float size );
	virtual void Draw( Graphics& gfx ) const override;
private:
	UINT idxCount;
};

