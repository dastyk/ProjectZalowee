#include "ModelClass.h"
#include "SystemClass.h"

ModelClass::ModelClass()
{
}


ModelClass::~ModelClass()
{
	// Release the vertex buffer
	if (mVertexBuffer)
	{
		mVertexBuffer->Release();
		mVertexBuffer = nullptr;
	}
	//Release the index buffer
	if (mIndexBuffer)
	{
		mIndexBuffer->Release();
		mIndexBuffer = nullptr;
	}
}


void ModelClass::SetAsModelToBeDrawn()const
{
	ID3D11DeviceContext* c = SystemClass::GetInstance()->mGrapInst->GetContext();

	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = mStride;
	offset = 0;

	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.

	c->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	c->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set topology
	c->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

UINT ModelClass::GetIndexCount()const
{
	return mIndexCount;
}











int ModelClass::CreateStaticVertexBuffer(ID3D11Buffer** ppVB, void* pData, UINT byteWidth)
{
	HRESULT hr;

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = pData;
	vinitData.SysMemPitch = 0;
	vinitData.SysMemSlicePitch = 0;

	D3D11_BUFFER_DESC vbd;
	memset(&vbd, 0, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = byteWidth;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	hr = SystemClass::GetInstance()->mGrapInst->GetDevice()->CreateBuffer(&vbd, &vinitData, ppVB);
	if (FAILED(hr))
	{
		MessageBox(0, L"Failed to create static Vertex Buffer.", 0, 0);
		return -16;
	}

	return 0;
}

int ModelClass::CreateDynamicVertexBuffer(ID3D11Buffer** ppVB, UINT maxByteWidth)
{
	HRESULT hr;

	D3D11_BUFFER_DESC vbd;
	memset(&vbd, 0, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = maxByteWidth;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	hr = SystemClass::GetInstance()->mGrapInst->GetDevice()->CreateBuffer(&vbd, NULL, ppVB);
	if (FAILED(hr))
	{
		MessageBox(0, L"Failed to create dynamic Vertex Buffer.", 0, 0);
		return -17;
	}

	return 0;
}


int ModelClass::CreateStaticIndexBuffer(ID3D11Buffer** ppIB, void* pData, UINT byteWidth)
{
	HRESULT hr;


	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = pData;
	iinitData.SysMemPitch = 0;
	iinitData.SysMemSlicePitch = 0;

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = byteWidth;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	hr = SystemClass::GetInstance()->mGrapInst->GetDevice()->CreateBuffer(&ibd, &iinitData, ppIB);
	if (FAILED(hr))
	{
		MessageBox(0, L"Failed to create static Index Buffer.", 0, 0);
		return -18;
	}
	return 0;
}

int ModelClass::CreateDynamicIndexBuffer(ID3D11Buffer** ppIB, UINT maxByteWidth)
{
	HRESULT hr;
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_DYNAMIC;
	ibd.ByteWidth = maxByteWidth;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	hr = SystemClass::GetInstance()->mGrapInst->GetDevice()->CreateBuffer(&ibd, NULL, ppIB);
	if (FAILED(hr))
	{
		MessageBox(0, L"Failed to create dynamic Index Buffer.", 0, 0);
		return -19;
	}
	return 0;
}
