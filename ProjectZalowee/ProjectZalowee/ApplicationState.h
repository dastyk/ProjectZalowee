#ifndef _APPLICATIONSTATE_H_
#define _APPLICATIONSTATE_H_

#pragma once
//////////////////
//	Includes	//
//////////////////
#include <vector>

using namespace std;
//////////////////////////
//	My Class Includes	//
//////////////////////////
#include "GraphicsObject.h"

class ApplicationState
{
protected:
	ApplicationState();
	virtual ~ApplicationState();

	vector<GraphicsObject*> mGraphicsObjects;

public:

	virtual int Init();
	virtual int HandleInput();
	virtual int Update(float dt);
	virtual int Render();
};

#endif