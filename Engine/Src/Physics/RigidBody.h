#pragma once
#include "Vec2.h"

class PhysicsEntity
{
public:
	void Update( float dt )
	{
		velocity += acceleration;
		position += velocity * dt;
	}
protected:
	PhysicsEntity( float m, Vec2& pos, Vec2 v, Vec2 a )
		: position( pos )
		, velocity( v )
		, acceleration( a )
		, mass( m )
	{}
private:
	float mass;
	Vec2& position;
	Vec2 velocity;
	Vec2 acceleration;
};