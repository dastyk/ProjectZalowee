#include "SystemClass.h"

SystemClass* SystemClass::mInstance = nullptr;

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Memoryleak detection.

	// Create and run the system object.
	return SystemClass::CreateInstance();

}

SystemClass::SystemClass()
{
}


SystemClass::~SystemClass()
{
	// Delete the graphics object
	if (mGrapInst)
	{
		delete mGrapInst;
		mGrapInst = 0;
	}
	// Delete the app object
	if (mAppInst)
	{
		delete mAppInst;
		mAppInst = 0;
	}
	// Delete the input object
	if (mInput)
	{
		delete mInput;
		mInput = 0;
	}
	// Delete the resource creater object
	if (mCreator)
	{
		delete mCreator;
		mCreator = 0;
	}
}


SystemClass* SystemClass::GetInstance()
{
	return mInstance;
}

int SystemClass::CreateInstance()
{
	int result;

	// Create the System Object and save a reference to it.
	static SystemClass inst;
	mInstance = &inst;
	if (!mInstance) return -1;

	// Create the resource creator
	result = mInstance->CreateCreator();
	if (result) return result;

	// Create the input class
	result = mInstance->CreateInputClass();
	if (result) return result;

	// Create the application
	result = mInstance->CreateApplication();
	if (result) return result;

	// Create the graphics class
	result = mInstance->CreateGraphics();
	if (result) return result;

	// Run the application
	return mInstance->mAppInst->Run();
	
}

int SystemClass::CreateApplication()
{
	int result;

	// Create the App Object
	mAppInst = new ApplicationClass;
	if (!mAppInst) return -3;

	// Initialize the app object
	result = mAppInst->Init();
	if (result) return result;

	return 0;
}

int SystemClass::CreateGraphics()
{
	int result;

	// Create the graphics object
	mGrapInst = new GraphicsClass;
	if (!mGrapInst) return -6;

	// Initialize the graphics object
	result = mGrapInst->Init();
	if (result) return result;

	return 0;
}

int SystemClass::CreateCreator()
{

	// Create the resource creater object
	mCreator = new ResourceCreator;
	if (!mCreator) return -2;

	return 0;
}

int SystemClass::CreateInputClass()
{
	int result;

	// Create the input object
	mInput = new InputClass;
	if (!mInput) return -7;

	// Init the input class
	result = mInput->Init();
	if (result) return result;

	return 0;
}