#pragma once
#include "Bindable.h"
#include "Macros.h"
#include "BindableCodex.h"
#include <vector>
#include <wrl.h>
#include <cassert>

namespace Binds
{


	class VertexBuffer : public Bindable
	{
	public:
		template <class Vertex>
		VertexBuffer( Graphics& gfx, const std::vector<Vertex>& vertices, std::string tag );
		void Bind( Graphics& gfx ) override
		{
			const UINT offset = 0u;
			pGetContext( gfx )->IASetVertexBuffers( 0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset );
		}
		template <class Vertex>
		static std::string GenerateUID( const std::vector<Vertex>& vertices, std::string tag )
		{
			return std::string( typeid( VertexBuffer ).name() ) + tag;
		}
		template <class Vertex>
		static std::shared_ptr<VertexBuffer>
			Resolve( Graphics& gfx, const std::vector<Vertex>& vertices, std::string tag )
		{
			return Binds::Codex::Resolve<VertexBuffer>( gfx, vertices, tag );
		}
	protected:
		VertexBuffer() = default;
		Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
		UINT stride;
	};

	template<class Vertex>
	VertexBuffer::VertexBuffer( Graphics& gfx, const std::vector<Vertex>& vertices, std::string tag )
	{
		assert( vertices.size() > 0 );
		// Error checker
		HRESULT hr;

		D3D11_SUBRESOURCE_DATA srd = { 0 };
		srd.pSysMem = vertices.data();
		srd.SysMemPitch = 0u; // Texture
		srd.SysMemSlicePitch = 0u;

		D3D11_BUFFER_DESC bd = { 0 };
		bd.ByteWidth = (UINT)( sizeof( Vertex ) * vertices.size() );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.StructureByteStride = sizeof( Vertex );

		THROW_FAILED_GFX( pGetDevice( gfx )->CreateBuffer( &bd, &srd, &pVertexBuffer ) );
		// Store stride based off templated vertex for use in binding
		stride = sizeof( Vertex );
	}
	
	/******************** Dynamic ****************************************************************/
	template <class Vertex>
	class DynamicVertexBuffer : public VertexBuffer
	{
	public:
		DynamicVertexBuffer( Graphics& gfx, const std::vector<Vertex>& vertices )
		{
			assert( vertices.size() > 0);
			// Error checker
			HRESULT hr;

			D3D11_SUBRESOURCE_DATA srd = { 0 };
			srd.pSysMem = vertices.data();
			srd.SysMemPitch = 0u; // Texture
			srd.SysMemSlicePitch = 0u;

			D3D11_BUFFER_DESC bd = { 0 };
			bd.ByteWidth = (UINT)( sizeof( Vertex ) * vertices.size() );
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bd.MiscFlags = 0u;
			bd.StructureByteStride = sizeof( Vertex );

			THROW_FAILED_GFX( pGetDevice( gfx )->CreateBuffer( &bd, &srd, &pVertexBuffer ) );
			// Store stride based off templated vertex for use in binding
			stride = sizeof( Vertex );
		}
		void Update( Graphics& gfx, const std::vector<Vertex>& vertices ) const
		{
			// Get data on const buffer and lock gpu from accessing it to write data
			D3D11_MAPPED_SUBRESOURCE msr;
			pGetContext( gfx )->Map( pVertexBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD,
									 0u, &msr );
			memcpy( msr.pData, vertices.data(), ( sizeof( Vertex ) * vertices.size() ) );
			pGetContext( gfx )->Unmap( pVertexBuffer.Get(), 0u );
		}
	};
};