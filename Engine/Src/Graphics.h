#pragma once
#include "Win.h"
#include "Core/BaseException.h"
#include "Camera.h"
#include <Render/Renderer.h>
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <memory>

class RenderTarget;
class Point;
class Color;

class Graphics
{
private:
	friend class GraphicsResource;	
public:
	class Exception : public BaseException
	{
	public:
		Exception( int line, const std::string& file, HRESULT hr );
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorString() const noexcept;
		HRESULT GetErrorCode() const noexcept;
		// Static function to translate error code, can be used statically
		static std::string TranslateErrorCode( HRESULT hRes ) noexcept;
	private:
		HRESULT hr;
	};
public:
	Graphics( HWND hWnd );
	~Graphics();
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
public:
	void BeginFrame();
	void Draw( UINT vertexCount, UINT start );
	void ExecuteRenderer();
	void DrawIndexed( UINT indexCount );
	std::shared_ptr<RenderTarget> pGetRenderTarget();
	void EndFrame();
	UINT GetWidth() const;
	UINT GetHeight() const;
public:
	Camera camera;
	Renderer renderer;
private:
	// Dimensions of client area
	UINT Width;
	UINT Height;
private:
	Microsoft::WRL::ComPtr<ID3D11Device>        pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain>      pSwapChain;
	std::shared_ptr<RenderTarget> pRenderTarget;
private:
	/********************** Parameters *******************/
	static constexpr bool enableVSync = true;

};

