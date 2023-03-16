#pragma once
#include <log.h>

class Point
{
public:
	Point( float x, float y )
		: x( x )
		, y( y )
	{}
	Point() = default;
	Point( float* xy )
	{
		DCHECK_NOTNULL_F( xy, "Cannot construct point from nullptr." );
		x = *xy;
		y = *( xy + 1 );
	}
	Point operator+( float rhs )
	{
		return Point{ x + rhs, y + rhs };
	}
	Point operator+( const Point& rhs )
	{
		return Point{ x + rhs.x, y + rhs.y };
	}
private:
	float x;
	float y;
};