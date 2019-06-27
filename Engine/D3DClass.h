#pragma once

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>


class D3DClass
{
public:
	D3DClass();
	~D3DClass();

	bool initialize(int, int, bool, HWND, bool, float, float);
	void shutdown();
	
	void beginScene(float, float, float, float);
	void endScene();

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

	void getProjectionMatrix(D3DXMATRIX&);
	void getWorldMatrix(D3DXMATRIX&);
	void getOrthoMatrix(D3DXMATRIX&);

	void getVideoCardInfo(char*, int&);

	void turnZBufferOn();
	void turnZBufferOff();

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_pSwapChain;
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11Texture2D* m_pDepthStencilBuffer;
	ID3D11DepthStencilState* m_pDepthStencilState;
	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11RasterizerState* m_pRasterState;
	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_worldMatrix;
	D3DXMATRIX m_orthoMatrix;
	ID3D11DepthStencilState* m_pDepthDisabledStencilState;
};