#include "ColorShader.h"
#include "SystemClass.h"

ColorShader::ColorShader()
{
}


ColorShader::~ColorShader()
{
	// Release the buffer
	if (mTranslationColorBuffer)
	{
		mTranslationColorBuffer->Release();
		mTranslationColorBuffer = 0;
	}
}

int ColorShader::Init()
{
	int result;


	D3D11_INPUT_ELEMENT_DESC vertexDesc[]=
	{
		{ "POSITION",0, DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};

	int numElements = sizeof(vertexDesc) / sizeof(vertexDesc[0]);

	/// Create the vertex shader and input layout
	result = CreateVertexShaderAndInputLayout(&mVertexShader, L"data/shaders/ColorVertexShader.hlsl", "VSMain", &mLayout, vertexDesc, numElements);
	if (result) return result;


	/// Create the pixel shader
	result = CreatePixelShader(&mPixelShader, L"data/shaders/ColorPixelShader.hlsl", "PSMain");
	if (result) return result;

	// Create the constant buffer
	result = CreateConstantBuffer(&mTranslationColorBuffer, sizeof(TCBuffer), D3D11_BIND_CONSTANT_BUFFER);
	if (result) return result;

	return 0;
}

int ColorShader::Render(XMMATRIX* translation, int modelID)
{
	ID3D11DeviceContext* c = SystemClass::GetInstance()->mGrapInst->GetContext();
	int width = SystemClass::GetInstance()->mAppInst->GetClientWidth();
	int height = SystemClass::GetInstance()->mAppInst->GetClientHeight();

	XMMATRIX ortho = XMMatrixOrthographicRH(width, height, 0, 1000);

	TCBuffer buf;
	XMMATRIX world = XMMatrixTranslation(-width / 2.0f, height/2.0f, 0);
	XMMATRIX scale = XMMatrixScaling(400, 400, 0);
	XMStoreFloat4x4(&buf.world, XMMatrixTranspose(*translation*scale*world*ortho));
	buf.color = XMFLOAT4(1, 0, 0, 1);

	// Send the data to the constant buffer
	int result = SetConstantBufferParameters(mTranslationColorBuffer, (void*)&buf, sizeof(TCBuffer));
	if (result) return result;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	c->VSSetConstantBuffers(0, 1, &mTranslationColorBuffer);

	RenderShader(6, 0);

	return 0;
}