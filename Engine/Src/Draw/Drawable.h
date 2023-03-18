#pragma once
#include <Physics/Vec2.h>
#include <vector>
#include <memory>
#include <DirectXMath.h>
#include <Binds/ConstantBuffers.h>

class Graphics;
class Bindable;

class Drawable
{
	friend class PhysicsEntity;

	struct ConstBuffer
	{
		DirectX::XMMATRIX model;
		DirectX::XMMATRIX viewproj;
	};
public:
	virtual void Draw( Graphics& gfx ) const = 0;
protected:
	Drawable( Graphics& gfx );;
	void AddBind( std::unique_ptr<Bindable> bind );
	virtual void BindAll( Graphics& gfx ) const;
	virtual void UpdateTransformBuffer(Graphics& gfx);
protected:
	Vec2 Position{ 0,0 };
	float Rotation = 0.f;
	float ScaleWidth = 1.f;
	float ScaleHeight = 1.f;
private:
	ConstBuffer CBData;
	std::vector<std::unique_ptr<Bindable>> BindPtrs;
	std::unique_ptr<Binds::VertexConstantBuffer<ConstBuffer>> pTransformCB;
};