#include "Ball.h"
#include <Draw/Circle.h>
#include <Physics/System.h>
#include <Physics/RigidBody.h>


Ball::Ball(Graphics& gfx, Phys::System* physics, Vec2 pos, float radius, float mass)
	: RigidBodyEntity(gfx,physics, std::make_shared<Circle>(gfx, 30), pos, radius, radius)
	, radius(radius)
{
}
