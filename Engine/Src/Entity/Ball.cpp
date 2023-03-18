#include "Ball.h"
#include <Draw/Circle.h>

Ball::Ball( Graphics& gfx,  Vec2 pos, float radius )
	: BaseEntity(gfx.renderer, std::make_unique<Circle>(gfx, pos, radius, 18))
{
}
