#pragma once
#include "Drawable.h"
#include <Util/Rect.h>

class Point;

class Quad : public Drawable
{
	using UINT = unsigned int;
public:
	Quad( Graphics& gfx, Rect rect );
	virtual void Draw( Graphics& gfx ) const override;
private:
	UINT idxCount;
};

