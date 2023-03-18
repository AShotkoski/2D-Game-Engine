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
	friend class BaseEntity;

	struct ConstBuffer
	{
		DirectX::XMMATRIX model;
		DirectX::XMMATRIX viewproj;
	};
public:
	virtual void Draw( Graphics& gfx ) const = 0;
protected:
	Drawable( Graphics& gfx);
	void AddBind( std::unique_ptr<Bindable> bind );
	virtual void BindAll( Graphics& gfx ) const;
	virtual void UpdateTransformBuffer(Vec2 pos, float theta, float width, float height, Graphics& gfx);
	virtual void UpdateTransformBufferCamera(Graphics& gfx); // only camera
private:
	ConstBuffer CBData;
	std::vector<std::unique_ptr<Bindable>> BindPtrs;
	std::unique_ptr<Binds::VertexConstantBuffer<ConstBuffer>> pTransformCB;
};