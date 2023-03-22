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
	virtual void BindAll( Graphics& gfx ) const;
	UINT GetIndicesCount() const;
protected:
	Drawable( Graphics& gfx);
	void AddBind( std::shared_ptr<Bindable> bind );
	virtual void UpdateTransformBuffer(Vec2 pos, float theta, float width, float height, Graphics& gfx);
	virtual void UpdateTransformBufferCamera(Graphics& gfx); 
	void SetIndicesCount(UINT count);
private:
	ConstBuffer                                               CBData;
	std::vector<std::shared_ptr<Bindable>>                    BindPtrs;
	std::unique_ptr<Binds::VertexConstantBuffer<ConstBuffer>> pTransformCB;

	UINT IndicesCount = 0u;
};