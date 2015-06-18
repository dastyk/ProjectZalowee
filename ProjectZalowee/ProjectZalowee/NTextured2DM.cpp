#include "NTextured2DM.h"


NTextured2DM::NTextured2DM()
{
}


NTextured2DM::~NTextured2DM()
{
}

int NTextured2DM::Init()
{
	int result;

	mStride = sizeof(VertexDesc);
	const UINT vertexCount = 4;
	VertexDesc vertices[vertexCount] = 
	{
		{ XMFLOAT2(-1.0f, -1.0f) },
		{ XMFLOAT2(-1.0f, 1.0f) },
		{ XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT2(1.0f, -1.0f) }
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