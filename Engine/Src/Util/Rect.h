#pragma once
#include <Physics/Vec2.h>

// data is top, bottom, left, right (32 bit float)
class Rect
{
public:
	static Rect Make( Vec2 topleft, Vec2 bottomright )
	{
		return Rect{ topleft.y, bottomright.y, topleft.x, bottomright.x };
	}
	static Rect Make( Vec2 center, float halfwidth, float halfheight )
	{
		return Rect{ center.y + halfheight, center.y - halfheight, center.x - halfwidth, center.x + halfwidth };
	}
	Vec2 GetCenter() const
	{
		return Vec2{ (left + right) / 2.f, (bottom + top) / 2.f };
	}
	float GetWidth() const
	{
		return right - left;
	}
	float GetHeight() const
	{
		return top - bottom;
	}
public:
	float top;
	float bottom;
	float left;
	float right;
};