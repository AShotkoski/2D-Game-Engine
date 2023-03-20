#include "InputLayout.h"
#include "Macros.h"
#include <cassert>
#include "BindableCodex.h"

namespace Binds
{

	InputLayout::InputLayout( Graphics& gfx,
							  const std::vector<D3D11_INPUT_ELEMENT_DESC>& descriptions,
							  ID3DBlob& VSByteCode )
	{
		// error handling
		HRESULT hr;
		assert( descriptions.size() > 0 );

		THROW_FAILED_GFX( pGetDevice( gfx )->CreateInputLayout(
			descriptions.data(),
			(UINT)descriptions.size(),
			VSByteCode.GetBufferPointer(),
			VSByteCode.GetBufferSize(),
			&pInputLayout ) );
	}

	void InputLayout::Bind( Graphics& gfx )
	{
		pGetContext( gfx )->IASetInputLayout( pInputLayout.Get() );
	}

	std::string InputLayout::GenerateUID( const std::vector<D3D11_INPUT_ELEMENT_DESC>& descriptions, ID3DBlob& )
	{
		using namespace std::string_literals;
		std::string descname;
		for ( const auto& d : descriptions )
		{
			descname += d.SemanticName;
		}
		return std::string(typeid(InputLayout).name() + "_"s + descname);
	}

	std::shared_ptr<InputLayout> InputLayout::Resolve( Graphics& gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& descriptions, ID3DBlob& VSByteCode )
	{
		return Binds::Codex::Resolve<InputLayout>(gfx,descriptions,VSByteCode);
	}


};