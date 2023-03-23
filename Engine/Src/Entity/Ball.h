#pragma once
#include "RigidBodyEntity.h"

class Graphics;
namespace Phys
{
	class System;
}

class Ball : public RigidBodyEntity
{
public:
	Ball( Graphics& gfx, Phys::System* physics,  Vec2 pos, float radius = 1.f, float mass = 1.f );
	void Update( float dt )
	{
		//calcAcc(dt);
		//vel += acc * dt;
		//shittybounce( -6.f );
		//position += vel * dt;
		UpdateModel();
	}
	void shittybounce( float floor_level )
	{
			// pure elastic : vel(final) = ( vel * ( mass - groundmass ) + groundvel * ( 2 * groundmass ) ) / ( mass + groundmass )
		constexpr float coef_of_restitution = 0.85f;
		if ( position.y - height <= floor_level )
		{
			vel *= coef_of_restitution;
			vel = -vel;

			//vel = 0;
			position.y += ( floor_level - (position.y - height) );
		}
	}
	void ApplyImpl( Vec2 impl )
	{
		// impl is N * s (newton times second) 
		netimpulse = impl;
	}
private:
	void calcAcc(float dt)
	{
		// a = net force / m
		
		// calc net forces from impulses
		netforce += netimpulse / dt;

		//apply gravity
		netforce.y += -9.8f * mass;

		acc = netforce / mass;
		netforce = 0;
		netimpulse = 0;
	}
private:
	float radius;
	Vec2 vel{ 0,0 };		// m/s
	Vec2 acc{ 0, 0 };		// m/s^2
	Vec2 netimpulse = {};
	Vec2 netforce{ 0,0 };	// kg * m/s^2
	float mass = 1.f;		// kg
	// Joule is kg * m^2 / s^2 == newton * meter
};

