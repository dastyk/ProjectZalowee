#ifndef _NULLSTATE_H_
#define _NULLSTATE_H_

#pragma once
//////////////////
//	Includes	//
//////////////////

//////////////////////////
//	My Class Includes	//
//////////////////////////
#include "ApplicationState.h"

class NullState :
	public ApplicationState
{
public:
	NullState();
	~NullState();

	int Init();
	int HandleInput();
	int Update(float dt);
	int Render();
};

#endif