#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#pragma once

//////////////////
//	Includes	//
//////////////////
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#pragma comment (lib, "d3d11.lib")

//////////////////////////
//	My Class Includes	//
//////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	~GraphicsClass();

	int Init();
	int StartRender();
	int DrawModel(XMMATRIX* translation, int model)const;
	int EndRender()const;

	ID3D11Device* GetDevice()const;
	ID3D11DeviceContext* GetContext()const;
private:
	UINT m4xMsaaQuality; // Quality level of 4x MSAA
	bool mEnable4xMsaa;

	IDXGISwapChain* mSwapChain;
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mDeviceContext;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11Texture2D* mDepthStencilBuffer;
	ID3D11DepthStencilView* mDepthStencilView;


#if defined(DEBUG) || defined(_DEBUG)
	ID3D11Debug* mDebugger;
#endif

private:
	int CreateDeviceDeviceContextSwapChain(ID3D11Device** ppDevice, ID3D11DeviceContext** ppDeviceContext, IDXGISwapChain** ppSwapChain, UINT flags);
	int CreateBackBufferRenderTargetView(ID3D11RenderTargetView** ppRTV);
	int CreateDepthStencilBufferAndView(ID3D11Texture2D** ppDSB, ID3D11DepthStencilView** ppDSV);
	void SetViewPort(float x, float y, float w, float h);
};

#endif