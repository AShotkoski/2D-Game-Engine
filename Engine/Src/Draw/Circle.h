#pragma once
#include "Drawable.h"

class Circle : public Drawable
{
	using UINT = unsigned int;
public:
	Circle( Graphics& gfx, Point pos, float radius );
	virtual void Draw( Graphics& gfx ) const override;
private:
	float radius;
	UINT idxCount;
};

