#include "RigidBody.h"

void RigidBody::Update( float dt )
{
	velocity += acceleration;
	position += velocity * dt;
}
