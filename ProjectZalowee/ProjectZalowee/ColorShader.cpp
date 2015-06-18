#include "ColorShader.h"


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
	result = CreateVertexShaderAndInputLayout(&mVertexShader, L"fil", "VSMain", &mLayout, vertexDesc, numElements);
	if (result) return result;


	/// Create the pixel shader
	result = CreatePixelShader(&mPixelShader, L"Fli", "PSMain");
	if (result) return result;

	// Create the constant buffer
	result = CreateConstantBuffer(&mTranslationColorBuffer, sizeof(TCBuffer), D3D11_BIND_CONSTANT_BUFFER);
	if (result) return result;

	return 0;
}

int ColorShader::Render(XMMATRIX* translation, int modelID)
{
	return 0;
}