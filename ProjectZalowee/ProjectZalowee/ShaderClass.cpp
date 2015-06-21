#include "ShaderClass.h"
#include "SystemClass.h"

ShaderClass::ShaderClass()
{
}


ShaderClass::~ShaderClass()
{
	// Release the layout.
	if (mLayout)
	{
		mLayout->Release();
		mLayout = 0;
	}

	// Release the pixel shader.
	if (mPixelShader)
	{
		mPixelShader->Release();
		mPixelShader = 0;
	}

	// Release the vertex shader.
	if (mVertexShader)
	{
		mVertexShader->Release();
		mVertexShader = 0;
	}
	if (mGeometryShader)
	{
		mGeometryShader->Release();
		mGeometryShader = 0;
	}
	if (mHullShader)
	{
		mHullShader->Release();
		mHullShader = 0;
	}
	if (mDomainShader)
	{
		mDomainShader->Release();
		mDomainShader = 0;
	}
	if (mComputeShader)
	{
		mComputeShader->Release();
		mComputeShader = 0;
	}
}

const void ShaderClass::RenderShader(UINT indexCount, UINT indexStart)const
{
	ID3D11DeviceContext* c = SystemClass::GetInstance()->mGrapInst->GetContext();

	// Set the vertex input layout.
	c->IASetInputLayout(mLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	c->VSSetShader(mVertexShader, nullptr, 0);
	c->HSSetShader(mHullShader, nullptr, 0);
	c->DSSetShader(mDomainShader, nullptr, 0);
	c->GSSetShader(mGeometryShader, nullptr, 0);
	c->PSSetShader(mPixelShader, nullptr, 0);

	// Render mesh stored in active buffers
	c->DrawIndexed(indexCount, indexStart, 0);
}

int ShaderClass::SetConstantBufferParameters(ID3D11Buffer* pBuffer, void* pData, size_t byteWidth)
{
	ID3D11DeviceContext* c = SystemClass::GetInstance()->mGrapInst->GetContext();

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	// Lock the constant buffer so it can be written to.
	result = c->Map(pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return -34;
	}

	// Copt the data to the constant buffer.
	memcpy(mappedResource.pData, pData, byteWidth);

	// Unlock the constant buffer.
	c->Unmap(pBuffer, 0);


	return 0;
}

void ShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	std::ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(0, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

}

int ShaderClass::CreateVertexShaderAndInputLayout(ID3D11VertexShader** ppVS, WCHAR* fileName, char* EntryPoint, ID3D11InputLayout** ppIL, D3D11_INPUT_ELEMENT_DESC *vertexDesc, int numElements)
{
	int result;

	HRESULT hr;

	// Initialize the vertex shader
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* errorMessages;

	hr = D3DCompileFromFile(
		fileName,
		NULL,
		NULL,
		EntryPoint,
		"vs_5_0",
		0,
		0,
		&vertexShaderBuffer,
		&errorMessages);

	if (FAILED(hr))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessages)
		{
			OutputShaderErrorMessage(errorMessages, fileName);
			return -20;
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(0, fileName, L"Missing Shader File", MB_OK);
			return -21;
		}
	}

	// Create the vertex shader from the buffer.
	hr = SystemClass::GetInstance()->mGrapInst->GetDevice()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, ppVS);
	if (FAILED(hr))
	{
		MessageBox(0, L"Failed to create vertex shader", 0, MB_OK);
		return -22;
	}

	result = CreateInputLayout(ppIL, vertexDesc, vertexShaderBuffer, numElements);
	if (result) return result;

	vertexShaderBuffer->Release();

	return 0;
}

int ShaderClass::CreateVertexShader(ID3D11VertexShader** ppVS, WCHAR* fileName, char* EntryPoint)
{
	HRESULT hr;

	// Initialize the vertex shader
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* errorMessages;

	hr = D3DCompileFromFile(
		fileName,
		NULL,
		NULL,
		EntryPoint,
		"vs_5_0",
		0,
		0,
		&vertexShaderBuffer,
		&errorMessages);

	if (FAILED(hr))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessages)
		{
			OutputShaderErrorMessage(errorMessages, fileName);
			return -23;
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(0, fileName, L"Missing Shader File", MB_OK);
			return -24;
		}
	}

	// Create the vertex shader from the buffer.
	hr = SystemClass::GetInstance()->mGrapInst->GetDevice()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, ppVS);
	if (FAILED(hr))
	{
		MessageBox(0, L"Failed to create vertex shader", 0, MB_OK);
		return -25;
	}

	vertexShaderBuffer->Release();

	return 0;
}

int ShaderClass::CreatePixelShader(ID3D11PixelShader** ppPS, WCHAR* fileName, char* EntryPoint)
{
	HRESULT hr;
	// Initialie Pixel shader
	ID3D10Blob* pixelShaderBuffer;
	ID3D10Blob* errorMessages;
	hr = D3DCompileFromFile(
		fileName,
		NULL,
		NULL,
		EntryPoint,
		"ps_5_0",
		0,
		0,
		&pixelShaderBuffer,
		&errorMessages);

	if (FAILED(hr))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessages)
		{
			OutputShaderErrorMessage(errorMessages, fileName);
			return -26;
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(0, fileName, L"Missing Shader File", MB_OK);
			return -27;
		}
	}

	// Create the pixel shader from the buffer.
	hr = SystemClass::GetInstance()->mGrapInst->GetDevice()->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, ppPS);
	if (FAILED(hr))
	{
		MessageBox(0, L"Failed to create pixel shader", 0, MB_OK);
		return -28;
	}

	pixelShaderBuffer->Release();
	return 0;
}

int ShaderClass::CreateGeometryShader(ID3D11GeometryShader** ppGS, WCHAR* fileName, char* EntryPoint)
{
	HRESULT hr;
	// Initialie Geometry shader
	ID3D10Blob* geometryShaderBuffer;
	ID3D10Blob* errorMessages;
	hr = D3DCompileFromFile(
		fileName,
		NULL,
		NULL,
		EntryPoint,
		"gs_5_0",
		0,
		0,
		&geometryShaderBuffer,
		&errorMessages);

	if (FAILED(hr))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessages)
		{
			OutputShaderErrorMessage(errorMessages, fileName);
			return -29;
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(0, fileName, L"Missing Shader File", MB_OK);
			return -30;
		}
	}

	// Create the geometry shader from the buffer.
	hr = SystemClass::GetInstance()->mGrapInst->GetDevice()->CreateGeometryShader(geometryShaderBuffer->GetBufferPointer(), geometryShaderBuffer->GetBufferSize(), NULL, ppGS);
	if (FAILED(hr))
	{
		MessageBox(0, L"Failed to create geometry shader", 0, MB_OK);
		return -31;
	}

	geometryShaderBuffer->Release();
	return 0;
}

int ShaderClass::CreateInputLayout(ID3D11InputLayout** ppIL, D3D11_INPUT_ELEMENT_DESC* pVertexDesc, ID3D10Blob* pVertexShaderBuffer, int numElements)
{
	HRESULT hr;

	// Create the input layout form the vertexshaderbuffer and vertexdesc
	hr = SystemClass::GetInstance()->mGrapInst->GetDevice()->CreateInputLayout(
		pVertexDesc,
		numElements,
		pVertexShaderBuffer->GetBufferPointer(),
		pVertexShaderBuffer->GetBufferSize(),
		ppIL);

	if (FAILED(hr))
	{
		MessageBox(0, L"Could not create input layout.", 0, 0);
		return -32;
	}

	return 0;
}


int ShaderClass::CreateConstantBuffer(ID3D11Buffer** ppBuffer, UINT byteWidth, UINT bindFlags)
{
	HRESULT hr;

	// Setup the description of the dynamic matrix constant buffer.
	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = byteWidth;
	matrixBufferDesc.BindFlags = bindFlags;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;


	// Create the constant buffer pointer so we can access the constant buffer from within this class.
	hr = SystemClass::GetInstance()->mGrapInst->GetDevice()->CreateBuffer(&matrixBufferDesc, NULL, ppBuffer);
	if (FAILED(hr))
	{
		MessageBox(0, L"Could not create constant buffer.", 0, 0);
		return -33;
	}

	return 0;
}