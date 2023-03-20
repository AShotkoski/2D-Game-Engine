#include "Ball.h"
#include <Draw/Circle.h>

Ball::Ball( Graphics& gfx, Vec2 pos, float radius )
	: BaseEntity(gfx, std::make_shared<Circle>(gfx, 30), pos, radius, radius)
	, radius(radius)
{
}
