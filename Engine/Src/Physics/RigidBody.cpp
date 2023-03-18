#include "PhysicsEntity.h"

void PhysicsEntity::Update( float dt )
{
	velocity += acceleration;
	position += velocity * dt;
}
