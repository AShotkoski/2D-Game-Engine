#pragma once
#include <Physics/Vec2.h>
#include <memory>

class Renderer;
class Drawable;

class BaseEntity
{
protected:
	BaseEntity( Renderer& Renderer, std::unique_ptr<Drawable> model  );
protected:
	Vec2 Position{ 0,0 };
};