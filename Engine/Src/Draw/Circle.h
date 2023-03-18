#pragma once
#include "Drawable.h"

class Circle : public Drawable
{
	using UINT = unsigned int;
public:
	Circle( Graphics& gfx, Point pos, float radius, size_t resolution = 12 );
	virtual void Draw( Graphics& gfx ) const override;
private:
	float radius;
	UINT idxCount;
};

