#include "NTextured2DM.h"
#include "SystemClass.h"

NTextured2DM::NTextured2DM()
{
}


NTextured2DM::~NTextured2DM()
{
}

int NTextured2DM::Init()
{
	int result;

	int width = SystemClass::GetInstance()->mAppInst->GetClientWidth();
	int height = SystemClass::GetInstance()->mAppInst->GetClientHeight();

	mStride = sizeof(VertexDesc);
	const UINT vertexCount = 4;
	VertexDesc vertices[vertexCount] = 
	{
		{ XMFLOAT2(0.0f, -height / (float)width) },
		{ XMFLOAT2(-0.0f, 0.0f) },
		{ XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT2(1.0f, -height / (float)width) }
	};

	result = CreateStaticVertexBuffer(&mVertexBuffer, vertices, sizeof(VertexDesc)*vertexCount);
	if (result) return result;

	const UINT indexCount = 6;
	mIndexCount = indexCount;
	UINT indices[indexCount] =
	{
		0, 1, 2,
		0, 2, 3
	};

	result = CreateStaticIndexBuffer(&mIndexBuffer, indices, sizeof(UINT)*indexCount);
	if (result) return result;

	return 0;
}