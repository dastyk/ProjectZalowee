#ifndef _APPLICATIONSTATE_H_
#define _APPLICATIONSTATE_H_

#pragma once
//////////////////
//	Includes	//
//////////////////

//////////////////////////
//	My Class Includes	//
//////////////////////////
class ApplicationState
{
protected:
	ApplicationState();
	virtual ~ApplicationState();

public:

	virtual int Init();
	virtual int HandleInput();
	virtual int Update(float dt);
	virtual int Render();
};

#endif