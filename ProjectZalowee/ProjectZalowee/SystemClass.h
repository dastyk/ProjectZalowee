#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

#pragma once


//////////////////////////
//	My Class Includes	//
//////////////////////////
#include "ApplicationClass.h"
#include "GraphicsClass.h"
#include "ResourceCreator.h"
#include "InputClass.h"

class SystemClass
{
private:
	SystemClass();
	SystemClass(const SystemClass& other);
	~SystemClass();
	SystemClass& operator=(const SystemClass& other);
private:
	static SystemClass* mInstance;

public:
	ApplicationClass* mAppInst;
	GraphicsClass* mGrapInst;
	ResourceCreator* mCreator;
	InputClass* mInput;

	int CreateApplication();
	int CreateGraphics();
	int CreateCreator();
	int CreateInputClass();
public:
	static SystemClass* GetInstance();
	static int CreateInstance();

};

#endif