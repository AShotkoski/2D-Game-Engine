#pragma once
#include "Bindable.h"
#include <vector>

namespace Binds
{

	class InputLayout : public Bindable
	{
	public:
		InputLayout( Graphics& gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& descriptions,
					 ID3DBlob& VSByteCode );
		void Bind( Graphics& gfx ) override;
		static std::string GenerateUID( const std::vector<D3D11_INPUT_ELEMENT_DESC>& descriptions, ID3DBlob& );
		static std::shared_ptr<InputLayout> Resolve( Graphics& gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& descriptions,
													 ID3DBlob& VSByteCode );
	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	};

};