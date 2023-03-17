#pragma once
#include <DirectXMath.h>

class Camera
{
public:
	Camera();
	void SetAspectRatio( float aspect_ratio );
	DirectX::XMMATRIX GetMatrix() const noexcept;
	DirectX::XMMATRIX GetMatrixWithProjection() const noexcept;
	void Reset() noexcept;
	void UpdatePosition( DirectX::XMFLOAT2 dPos, float dt );
	DirectX::XMFLOAT2 GetPosition( ) const;
	void UpdateMovementSpeed( float factor );
	bool isDirty() const;
	float GetZoom() const;
	void SetZoom( float zoom_amount );
	// Position for increase, negative decrease
	void UpdateZoom( float change_zoom );
private:
	void CalculateMatrices();
private:
	mutable bool dirty = false;
	DirectX::XMMATRIX view = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX projection = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT2 Position;
	float MoveSpeed = 8.5f;
	float zoom = 0.05f;
};

