#pragma once
#include "Drawable.h"

class Circle : public Drawable
{
	using UINT = unsigned int;
public:
	Circle( Graphics& gfx, size_t resolution = 12 );
};
