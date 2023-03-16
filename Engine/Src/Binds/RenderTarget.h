#pragma once
#include <Graphics.h>
#include <Binds/Bindable.h>


class RenderTarget : public Bindable
{
public:
	void Clear( Graphics& gfx ) const;
	virtual void Bind( Graphics& gfx ) override;
protected:
	RenderTarget( Graphics& gfx, UINT width, UINT height );
	RenderTarget( Graphics& gfx, ID3D11Texture2D* pTex );
	virtual void BindAsRT( Graphics& gfx, ID3D11DepthStencilView* pDS ) const;
	ID3D11RenderTargetView* pGetTargetView() const;
private:	
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTargetView;
	UINT Width;
	UINT Height;
};


// Note shaderinputrendertarget bind function will bind as render target, you must call 
// "BindAsTex" to bind as a texture for the PS

class ShaderInputRenderTarget : public RenderTarget
{
public:
	ShaderInputRenderTarget( Graphics& gfx, UINT width, UINT height );
	void BindAsTex( Graphics& gfx, UINT slot ) const;
protected:
	virtual void BindAsRT( Graphics& gfx, ID3D11DepthStencilView* pDS ) const override;
private:
	void BindNullShaderResource( Graphics& gfx ) const;
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
	// Used only for binding null shader rec
	mutable bool isResourceBound = false;
	mutable UINT SRVSlot = 0u;
};

// Render target may only be used as a render target
class ExclusiveRenderTarget : public RenderTarget
{
public:
	ExclusiveRenderTarget( Graphics& gfx, ID3D11Texture2D* pTexture )
		: RenderTarget(gfx, pTexture)
	{}
	// todo override bind functions to give error if called
};