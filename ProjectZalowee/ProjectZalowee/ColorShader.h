#ifndef _COLORSHADER_H_
#define _COLORSHADER_H_

#pragma once
//////////////////
//	Includes	//
//////////////////

//////////////////////////
//	My Class Includes	//
//////////////////////////
#include "ShaderClass.h"

///////////////
//	Structs	 //
///////////////
struct TCBuffer
{
	XMFLOAT4X4 world;
	XMFLOAT4 color;
};

class ColorShader :
	public ShaderClass
{
public:
	ColorShader();
	~ColorShader();

	int Init();
	int Render(XMMATRIX* translation, int modelID);

private:
	ID3D11Buffer* mTranslationColorBuffer;
};

#endif