#pragma once
#include <vector>
#include <memory>
#include <DirectXMath.h>
#include <Util/Point.h>
#include <Binds/ConstantBuffers.h>

class Graphics;
class Bindable;

class Drawable
{
	struct ConstBuffer
	{
		DirectX::XMMATRIX model;
		DirectX::XMMATRIX view;
	};
public:
	virtual void Draw( Graphics& gfx ) const = 0;
protected:
	Drawable( Graphics& gfx );;
	void AddBind( std::unique_ptr<Bindable> bind );
	virtual void BindAll( Graphics& gfx ) const;
	virtual void UpdateTransformBuffer(Graphics& gfx);
protected:
	Point Position{ 0,0 };
private:
	ConstBuffer CBData;
	std::vector<std::unique_ptr<Bindable>> BindPtrs;
	std::unique_ptr<Binds::VertexConstantBuffer<ConstBuffer>> pTransformCB;
};