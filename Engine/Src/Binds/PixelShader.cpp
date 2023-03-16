#include "PixelShader.h"
#include "Macros.h"
#include "Util/GeneralUtilities.h"
#include <log.h>
#include <filesystem>
#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

namespace Binds
{

	PixelShader::PixelShader( Graphics& gfx, const std::wstring path )
	{
		// error codes
		HRESULT hr;

		// Check file exists (will change later)
		DCHECK_F( std::filesystem::exists( path ), "Could not find pixel shader file: %s", Util::WStringToString( path ).c_str() );

		// Blob holds the binary of the shader
		Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

		THROW_FAILED_GFX( D3DReadFileToBlob( path.c_str(), &pBlob ) );
		
		THROW_FAILED_GFX( pGetDevice( gfx )->CreatePixelShader( pBlob->GetBufferPointer(),
																	pBlob->GetBufferSize(),
																	nullptr, &pPixelShader ) );
	}

	void PixelShader::Bind( Graphics& gfx )
	{
		pGetContext( gfx )->PSSetShader( pPixelShader.Get(), nullptr, 0u );
	}


};