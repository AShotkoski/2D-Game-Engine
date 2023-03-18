#pragma once

#include <DirectXMath.h>
#include <cmath>

class Vec2
{
public:
	Vec2() = default;
	Vec2( float x_in, float y_in ) : x( x_in ), y( y_in ) {}

	Vec2& operator=( float rhs )
	{
		x = rhs;
		y = rhs;
		return *this;
	}
	Vec2 operator+( const Vec2& rhs ) const
	{
		return Vec2( x + rhs.x, y + rhs.y );
	}
	Vec2 operator+( float rhs ) const
	{
		return Vec2( x + rhs, y + rhs );
	}
	Vec2& operator+=( float rhs )
	{
		return *this = *this + rhs;
	}
	Vec2& operator+=( const Vec2& rhs )
	{
		return *this = *this + rhs;
	}
	Vec2 operator-( const Vec2& rhs ) const
	{
		return Vec2( x - rhs.x, y - rhs.y );
	}
	Vec2& operator-=( const Vec2& rhs )
	{
		return *this = *this - rhs;
	}
	Vec2 operator*( float rhs ) const
	{
		return Vec2( x * rhs, y * rhs );
	}
	Vec2& operator*=( float rhs )
	{
		return *this = *this * rhs;
	}
	Vec2 operator/( float rhs ) const
	{
		return Vec2( x / rhs, y / rhs );
	}
	Vec2& operator/=( float rhs )
	{
		return *this = *this / rhs;
	}
	bool operator==( const Vec2& rhs )
	{
		return ( x == rhs.x && y == rhs.y );
	}
	bool operator!=( const Vec2& rhs )
	{
		return !( rhs == *this );
	}
	Vec2& operator-()
	{
		x = -x;
		y = -y;
		return *this;
	}
	const Vec2 operator-() const
	{
		return Vec2( -x, -y );
	}
	float dot( const Vec2& rhs ) const
	{
		return x * rhs.x + y * rhs.y;
	}
	float Length() const
	{
		return std::sqrt( LengthSq() );
	}
	float LengthSq() const
	{
		return float( x * x + y * y );
	}
	float DistToSq( const Vec2& other ) const
	{
		return ( ( other.x - x ) * ( other.x - x ) ) + ( ( other.y - y ) * ( other.y - y ) );
	}
	float DistTo( const Vec2& other ) const
	{
		return std::sqrt( DistToSq( other ) );
	}
	Vec2& Normalize()
	{
		return *this = GetNormalized();
	}
	Vec2 GetNormalized() const
	{
		const float len = Length();
		if( len != 0 )
		{
			return *this * ( 1.f / len );
		}
		return *this;
	}

public:
	float x;
	float y;
};