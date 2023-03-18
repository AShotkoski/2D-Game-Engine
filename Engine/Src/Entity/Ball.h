#pragma once
#include "BaseEntity.h"

class Graphics;

class Ball : public BaseEntity
{
public:
	Ball( Graphics& gfx, Vec2 pos, float radius );
};

