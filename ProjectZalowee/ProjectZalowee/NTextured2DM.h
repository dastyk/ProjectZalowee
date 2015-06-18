#ifndef _NTEXTURED2DM_H_
#define _NTEXTURED2DM_H_

#pragma once
//////////////////
//	Includes	//
//////////////////

//////////////////////////
//	My Class Includes	//
//////////////////////////
#include "Static2DM.h"

///////////////
//	Structs	 //
///////////////
struct VertexDesc
{
	XMFLOAT2 Pos;
};

class NTextured2DM :
	public Static2DM
{
public:
	NTextured2DM();
	virtual ~NTextured2DM();

	int Init();

};

#endif