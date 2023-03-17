#pragma once
#include "Drawable.h"

class Point;

class Quad : public Drawable
{
	using UINT = unsigned int;
public:
	// todo make it not be a square lmao
	Quad( Graphics& gfx, Point center, float size );
	virtual void Draw( Graphics& gfx ) const override;
	void SetPos( Point newPos );
	Point GetPos() const;
	void MarkDirty();
private:
	mutable bool dirty = false;
	UINT idxCount;
};

