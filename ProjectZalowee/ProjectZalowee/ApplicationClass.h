#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_

#pragma once

//////////////////
//	Includes	//
//////////////////
#include <Windows.h>
#include <Windowsx.h>
#include <string>

using namespace std;
//////////////////////////
//	My Class Includes	//
//////////////////////////
#include "TimerClass.h"

class ApplicationClass
{
public:
	ApplicationClass();
	~ApplicationClass();

	int Init();
	int Run();
	int ChangeState(int ID);

	int GetClientWidth();
	int GetClientHeight();
	HWND GetHWnd();
	bool IsFullScreen();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	int Frame();
	int HandleInput();
	int Update(float dt);
	int Render();

	int InitializeWindows();
	void ShutdownWindows();
private:
	HINSTANCE mHInst;
	HWND mHWnd;
	bool mRunning;
	bool mAppPaused;
	bool mMinimized;
	bool mMaximized;
	bool mResizing;
	bool mFullscreen;

	int mClientWidth;
	int mClientHeight;

	int mScreenWidth;
	int mScreenHeight;

	wstring mWNDCaption;


	TimerClass* mTimer;
};

/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


#endif