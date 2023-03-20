#pragma once
#include <Physics/Vec2.h>
#include <memory>

class Graphics;
class Drawable;

class BaseEntity
{
protected:
	BaseEntity( Graphics& gfx, std::shared_ptr<Drawable> model, 
				Vec2 pos, float width = 1.f, float height = 1.f, float rotation = 0.f );
	void UpdateModel() const;
protected:
	Vec2 position;
	float rotation;
	float width;
	float height;
	std::shared_ptr<Drawable> pModel;
	Graphics& gfx;
};