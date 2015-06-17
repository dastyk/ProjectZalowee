#include "GraphicsClass.h"
#include "SystemClass.h"

GraphicsClass::GraphicsClass()
{
	m4xMsaaQuality = 1; // Quality level of 4x MSAA
	mEnable4xMsaa = false;

	mSwapChain = nullptr;
	mDevice = nullptr;
	mDeviceContext = nullptr;
	mRenderTargetView = nullptr;
	mDepthStencilBuffer = nullptr;
	mDepthStencilView = nullptr;
}


GraphicsClass::~GraphicsClass()
{
	// Release the depthstencilView
	if (mDepthStencilView)
	{
		mDepthStencilView->Release();
		mDepthStencilView = nullptr;
	}
	// Release the depthstencilbuffer
	if (mDepthStencilBuffer)
	{
		mDepthStencilBuffer->Release();
		mDepthStencilBuffer = nullptr;
	}
	// Release the rendertargetview
	if (mRenderTargetView)
	{
		mRenderTargetView->Release();
		mRenderTargetView = nullptr;
	}
	// Release the swapchain
	if (mSwapChain)
	{
		mSwapChain->Release();
		mSwapChain = nullptr;
	}
	// Release the device context
	if (mDeviceContext)
	{
		mDeviceContext->Release();
		mDeviceContext = nullptr;
	}
	// Release the device
	if (mDevice)
	{
		mDevice->Release();
		mDevice = nullptr;
	}
#if defined(DEBUG) || defined(_DEBUG)
	if (mDebugger)
	{
		mDebugger->Release();
		mDebugger = 0;
	}
#endif
}


int GraphicsClass::Init()
{
	UINT createDeviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	int result;

	// Create Device,DeviceContext,Swapchain and dxgiAdapter
	result = CreateDeviceDeviceContextSwapChain(&mDevice, &mDeviceContext, &mSwapChain, createDeviceFlags);
	if (result) return result;

	// Create the render target view
	result = CreateBackBufferRenderTargetView(&mRenderTargetView);
	if (result) return result;

	// Create the depthstencilbuffer and view
	result = CreateDepthStencilBufferAndView(&mDepthStencilBuffer, &mDepthStencilView);
	if (result) return result;

	return 0;
}

int GraphicsClass::StartRender()
{
	// Set the viewport
	SetViewPort(0.0f, 0.0f, (float)SystemClass::GetInstance()->mAppInst->GetClientWidth(), (float)SystemClass::GetInstance()->mAppInst->GetClientHeight());

	// Set the render target view
	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	// Clear back buffer blue.
	float clearColor[] = { 0.4f, 0.4f, 0.9f, 1.0f };
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, clearColor);

	//// Clear depth buffer to 1.0f and stencil buffer to 0.
	mDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return 0;
}

int GraphicsClass::EndRender()
{
	HRESULT hr;

	// Present the back buffer to the screen
	hr = mSwapChain->Present(0, 0);
	if (FAILED(hr))
	{
		MessageBox(0, L"Failed to swap back buffer", 0, 0);
		return -15;
	}

	return 0;
}

int GraphicsClass::CreateDeviceDeviceContextSwapChain(ID3D11Device** ppDevice, ID3D11DeviceContext** ppDeviceContext, IDXGISwapChain** ppSwapChain, UINT flags)
{
	HRESULT hr;
	D3D_FEATURE_LEVEL featureLevel;

	DXGI_SWAP_CHAIN_DESC sd;
	// clear out the struct for use
	ZeroMemory(&sd, sizeof(sd));

	sd.BufferDesc.Width = SystemClass::GetInstance()->mAppInst->GetClientWidth();
	sd.BufferDesc.Height = SystemClass::GetInstance()->mAppInst->GetClientHeight();
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (mEnable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m4xMsaaQuality - 1;

	}
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS;
	sd.BufferCount = 1;
	sd.OutputWindow = SystemClass::GetInstance()->mAppInst->GetHWnd();
	sd.Windowed = (!SystemClass::GetInstance()->mAppInst->IsFullScreen());
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// Create Device and Context and SwapChain
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		flags,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&sd,
		ppSwapChain,
		ppDevice,
		&featureLevel,
		ppDeviceContext);
	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice and swapchain Failed.", 0, 0);
		return -8;
	}
	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return -9;
	}

	return 0;
}

int GraphicsClass::CreateBackBufferRenderTargetView(ID3D11RenderTargetView** ppRTV)
{
	HRESULT hr;

	ID3D11Texture2D* backBuffer;

	// Get pointer to backbuffer texture2d
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	if (FAILED(hr))
	{
		return -10;
	}
#if defined(DEBUG) || defined(_DEBUG)
	hr = mDevice->QueryInterface(__uuidof(ID3D11Debug), (void**)&mDebugger);
	if (FAILED(hr))
	{
		return -11;
	}
#endif

	// Create the render target view from the backbuffer texture2d
	hr = mDevice->CreateRenderTargetView(backBuffer, NULL, &mRenderTargetView);
	if (FAILED(hr))
	{
		return -12;
	}

	// Release the backbuffer texture2d since we dont need it any longer.
	backBuffer->Release();

	return 0;
}

int GraphicsClass::CreateDepthStencilBufferAndView(ID3D11Texture2D** ppDSB, ID3D11DepthStencilView** ppDSV)
{
	HRESULT hr;

	D3D11_TEXTURE2D_DESC depthBufferDesc;

	// Initialize the description of the depth buffer.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	depthBufferDesc.Width = SystemClass::GetInstance()->mAppInst->GetClientWidth();
	depthBufferDesc.Height = SystemClass::GetInstance()->mAppInst->GetClientHeight();
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D32_FLOAT;
	if (mEnable4xMsaa)
	{
		depthBufferDesc.SampleDesc.Count = 4;
		depthBufferDesc.SampleDesc.Quality = m4xMsaaQuality - 1;

	}
	else
	{
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
	}
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;


	// Create the depthstencilbuffer
	hr = mDevice->CreateTexture2D(&depthBufferDesc, 0, &mDepthStencilBuffer);
	if (FAILED(hr))
	{
		MessageBox(0, L"Could not create DepthStencilBuffer.", 0, 0);
		return -13;
	}


	// Create the depthstencilview from the depthstencilbuffer texture2d.
	hr = mDevice->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView);
	if (FAILED(hr))
	{
		MessageBox(0, L"Could not create DepthStencilview.", 0, 0);
		return -14;
	}

	return 0;
}

void GraphicsClass::SetViewPort(float x, float y, float w, float h)
{
	// Set viewport
	D3D11_VIEWPORT vp;
	vp.Width = w;
	vp.Height = w;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = x;
	vp.TopLeftY = y;

	mDeviceContext->RSSetViewports(1, &vp);
}