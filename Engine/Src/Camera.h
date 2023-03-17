#pragma once
#include <DirectXMath.h>

class Camera
{
public:
	Camera();
	DirectX::XMMATRIX GetMatrix() const noexcept;
	void Reset() noexcept;
	void UpdatePosition( DirectX::XMFLOAT2 dPos, float dt );
	DirectX::XMFLOAT2 GetPosition( ) const;
	void UpdateMovementSpeed( float factor );
private:
	void CalculateMatrices();
private:
	DirectX::XMMATRIX view = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT2 Position;
	// Only adjust the numerator
	float MoveSpeed = 15.f;
};

