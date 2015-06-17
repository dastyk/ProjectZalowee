////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "InputClass.h"

InputClass::InputClass()
{
	mMousePosX = mMousePosY = mLastMousePosX = mLastMousePosY = 0;
}


InputClass::~InputClass()
{

}


int InputClass::Init()
{
	// Initialize all the keys to being released and not pressed.
	for (int i = 0; i<256; i++)
	{
		mKeys[i] = false;
	}
	for (int i = 0; i<3; i++)
	{
		mMouseKeys[i] = false;
	}

	return 0;
}


void InputClass::KeyDown(unsigned int key)
{
	// If a key is pressed then save that state in the key array.
	mKeys[key] = true;
	return;
}


void InputClass::KeyUp(unsigned int key)
{
	// If a key is released then clear that state in the key array.
	mKeys[key] = false;
	return;
}

bool InputClass::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return mKeys[key];
}

bool InputClass::GetKeyStateAndReset(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed) then set state to false.
	bool temp = mKeys[key];
	mKeys[key] = false;
	return temp;
}

void InputClass::OnMouseMove(int x, int y)
{
	// If mouse is moved update last mouse position and save the new position.
	mLastMousePosX = mMousePosX;
	mLastMousePosY = mMousePosY;
	mMousePosX = x;
	mMousePosY = y;
}

void InputClass::MouseDown(unsigned int key)
{
	// If a key is pressed then save that state in the key array.
	mMouseKeys[key] = true;
}

void InputClass::MouseUp(unsigned int key)
{
	// If a key is released then clear that state in the key array.
	mMouseKeys[key] = false;
}

void InputClass::OnMouseScroll(int delta)
{
	// Add the delta to all scroll listeners.
	int count = mScrollListeners.size();
	for (int i = 0; i < count; i++)
	{
		(*(mScrollListeners[i])) += (delta / 10);
	}
}


bool InputClass::IsMouseKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return mMouseKeys[key];
}

bool InputClass::GetMouseKeyStateAndReset(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed) then set state to false.
	bool temp = mMouseKeys[key];
	mMouseKeys[key] = false;
	return temp;
}


void InputClass::GetMousePos(int &x, int &y)
{
	// Return the mouse position.
	x = mMousePosX;
	y = mMousePosY;
}

int InputClass::GetMousePosYDiff()
{
	// Get the difference of the y pos
	return mMousePosY - mLastMousePosY;
}



void InputClass::AddScrollListener(int* l)
{
	// Add a scroll listener. (Used for scrolling in TextList)
	mScrollListeners.push_back(l);
}