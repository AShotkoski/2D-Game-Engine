#pragma once
#include "Vec2.h"

class RigidBody
{
public:
	void Update( float dt );
protected:
	RigidBody( float m, Vec2& pos, Vec2 v, Vec2 a )
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