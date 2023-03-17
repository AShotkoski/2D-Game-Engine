#include "Camera.h"
#include <algorithm>

using namespace DirectX;

Camera::Camera()
{
	Reset();
}

void Camera::SetAspectRatio( float aspect_ratio )
{
	// Setup projection
	projection = DirectX::XMMatrixOrthographicLH( 1.f, 1.f / aspect_ratio, 0, 2.f );
}

DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{
	return view;
}
DirectX::XMMATRIX Camera::GetMatrixWithProjection() const noexcept
{
	return view * projection;
}
;

void Camera::Reset() noexcept
{
	Position.x = 0.f;
	Position.y = 0.f;
	CalculateMatrices();
}

void Camera::UpdatePosition( DirectX::XMFLOAT2 dPos, float dt )
{
	const float MoveSpeed = this->MoveSpeed * dt;

	// Update dPos to care about direction the camera is facing and the movespeed
	XMStoreFloat2( &dPos, XMVector2Transform(
		XMLoadFloat2( &dPos ),
		XMMatrixScaling( MoveSpeed, MoveSpeed, MoveSpeed )
	) );
	Position.x += dPos.x;
	Position.y += dPos.y;
	CalculateMatrices();
}

DirectX::XMFLOAT2 Camera::GetPosition() const
{
	return Position;
}

void Camera::UpdateMovementSpeed( float factor )
{
	assert( factor >= 0.f);
	MoveSpeed *= factor;
}

void Camera::CalculateMatrices()
{
	// Rotate where we want to look
	XMVECTOR base = XMVectorSet( 0, 0, 1.f, 0.f ); 

	auto xmpos = XMLoadFloat2( &Position );

	view = XMMatrixLookAtLH( xmpos, base + xmpos, XMVectorSet( 0, 1.f, 0, 0.f ) );
}
