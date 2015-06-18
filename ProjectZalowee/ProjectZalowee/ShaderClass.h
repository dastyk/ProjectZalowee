#ifndef _SHADERCLASS_H_
#define _SHADERCLASS_H_

#pragma once
//////////////////
//	Includes	//
//////////////////
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>

using namespace DirectX;
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

//////////////////////////
//	My Class Includes	//
//////////////////////////
class ShaderClass
{
public:
	ShaderClass();
	virtual ~ShaderClass();

	virtual int Init() = 0;
	virtual int Render(XMMATRIX* translation, int modelID) = 0;

protected:
	const void RenderShader(UINT indexCount, UINT indexStart) const;


	void OutputShaderErrorMessage(ID3D10Blob*, WCHAR*);

	int CreateVertexShaderAndInputLayout(ID3D11VertexShader** ppVS, WCHAR* fileName, char* EntryPoint, ID3D11InputLayout** ppIL, D3D11_INPUT_ELEMENT_DESC *vertexDesc, int numElements);
	int CreateVertexShader(ID3D11VertexShader** ppVS, WCHAR* fileName, char* EntryPoint);
	int CreatePixelShader(ID3D11PixelShader** ppPS, WCHAR* fileName, char* EntryPoint);
	int CreateGeometryShader(ID3D11GeometryShader** ppGS, WCHAR* fileName, char* EntryPoint);
	int CreateInputLayout(ID3D11InputLayout** ppIL, D3D11_INPUT_ELEMENT_DESC* pVertexDesc, ID3D10Blob* pVertexShaderBuffer, int numElements);
	
	int CreateConstantBuffer(ID3D11Buffer** ppBuffer, UINT byteWidth, UINT bindFlags);

protected:
	ID3D11VertexShader* mVertexShader;
	ID3D11PixelShader* mPixelShader;
	ID3D11GeometryShader* mGeometryShader;
	ID3D11HullShader* mHullShader;
	ID3D11DomainShader* mDomainShader;
	ID3D11ComputeShader* mComputeShader;

	ID3D11InputLayout* mLayout;
};

#endif