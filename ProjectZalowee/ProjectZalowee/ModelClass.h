#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#pragma once
//////////////////
//	Includes	//
//////////////////
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;
//////////////////////////
//	My Class Includes	//
//////////////////////////
class ModelClass
{
public:
	ModelClass();
	virtual ~ModelClass();

	virtual int Init() = 0;
	virtual void SetAsModelToBeDrawn()const;
	UINT GetIndexCount()const;

protected:
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;

	UINT mIndexCount;
	UINT mStride;
protected:
	int CreateStaticVertexBuffer(ID3D11Buffer** ppVB, void* pData, UINT byteWidth);
	int CreateDynamicVertexBuffer(ID3D11Buffer** ppVB, UINT maxByteWidth);

	int CreateStaticIndexBuffer(ID3D11Buffer** ppIB, void* pData, UINT byteWidth);
	int CreateDynamicIndexBuffer(ID3D11Buffer** ppIB, UINT maxByteWidth);
};

#endif