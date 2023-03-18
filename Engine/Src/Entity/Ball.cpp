#include "Ball.h"
#include <Draw/Circle.h>

Ball::Ball( Graphics& gfx,  Vec2 pos, float radius )
	: BaseEntity(gfx, std::make_unique<Circle>(gfx, 18), {0,5.f })
	, radius(radius)
{
}
