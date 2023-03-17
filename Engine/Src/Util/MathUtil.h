#pragma once
#include <DirectXMath.h>

static DirectX::XMFLOAT3X3 MatTo3x3( DirectX::XMMATRIX mat )
{
	DirectX::XMFLOAT3X3 ret;
	DirectX::XMStoreFloat3x3( &ret, std::move( mat ) );
	return ret;
}

static DirectX::XMFLOAT3 operator+( const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs )
{
	return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

static bool operator==( const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs )
{
	return { lhs.x == rhs.x &&  lhs.y  == rhs.y && lhs.z == rhs.z };
}