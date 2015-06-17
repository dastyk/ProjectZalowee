#include "ApplicationClass.h"
#include "SystemClass.h"

ApplicationClass::ApplicationClass()
{
	mHInst = nullptr;
	mHWnd = nullptr;
	mAppPaused = false;
	mMinimized = false;
	mMaximized = false;
	mResizing = false;
	mFullscreen = false;
	mRunning = false;

	mClientWidth = 800;
	mClientHeight = 600;

	mWNDCaption = L"Project Zalowee";
}


ApplicationClass::~ApplicationClass()
{
	// Release timer object
	if (mTimer)
	{
		delete mTimer;
		mTimer = nullptr;
	}

	// Shutdown the window
	ShutdownWindows();
}

int ApplicationClass::Init()
{
	int result;

	// The hinst and screen width and height
	mHInst = GetModuleHandle(NULL);
	mScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	mScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Create the window
	result = InitializeWindows();
	if (result) return result;

	// Create the game timer
	mTimer = new TimerClass;
	if (!mTimer) return -5;



	return 0;
}


int ApplicationClass::InitializeWindows()
{
	// Setup the windows class
	WNDCLASSEX wc;
	int posX, posY;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mHInst;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = mWNDCaption;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (mFullscreen)
	{

		mClientWidth = mScreenWidth;
		mClientHeight = mScreenHeight;

		DEVMODE dmScreenSettings;
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)mClientWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)mClientHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// Place the window in the middle of the screen.
		posX = (mScreenWidth - mClientWidth) / 2;
		posY = (mScreenHeight - mClientHeight) / 2;
	}


	RECT rc = { 0, 0, mClientWidth, mClientHeight };
	AdjustWindowRect(&rc, (WS_OVERLAPPED | WS_CAPTION), FALSE);


	// Create the window with the screen settings and get the handle to it.
	mHWnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		mWNDCaption,
		mWNDCaption,
		(WS_OVERLAPPED | WS_CAPTION),
		posX,
		posY,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		NULL,
		mHInst,
		NULL);

	if (!mHWnd)
	{
		MessageBox(0, L"Failed to create Window", 0, 0);
		return -4;
	}


	// Bring the window up on the screen and set it as main focus.
	ShowWindow(mHWnd, SW_SHOW);
	SetForegroundWindow(mHWnd);
	SetFocus(mHWnd);

	// Set the cursor to the middle of the client window
	SetCursorPos(posX + mClientWidth / 2, posY + mClientHeight / 2);

	return 0;
}

void ApplicationClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (mFullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(mHWnd);
	mHWnd = nullptr;

	// Remove the application instance.
	UnregisterClass(mWNDCaption, mHInst);
	mHInst = nullptr;

	return;
}

int ApplicationClass::Run()
{
	MSG msg;
	int result;

	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));


	// Reset the timer
	mTimer->Reset();

	// Loop until there is a quit message from the window or the user.
	mRunning = true;
	while (mRunning)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Do the frame processing.
		result = Frame();
		if (result)
		{
			mRunning = false;
		}


	}

	return result;
}

int ApplicationClass::ChangeState(int ID)
{
	return 0;
}

int ApplicationClass::Frame()
{
	int result;

	mTimer->Tick();


	// Handle input this frame
	result = HandleInput();
	if (result) return result;

	// Do any updates for the frame
	result = Update(mTimer->DeltaTime());
	if (result) return result;

	// Do any rendering for the frame
	result = Render();
	if (result) return result;

	return 0;
}

int ApplicationClass::HandleInput()
{

	return 0;
}

int ApplicationClass::Update(float dt)
{
	return 0;
}

int ApplicationClass::Render()
{
	SystemClass::GetInstance()->mGrapInst->StartRender();


	SystemClass::GetInstance()->mGrapInst->EndRender();
	return 0;
}


int ApplicationClass::GetClientWidth()
{
	return mClientWidth;
}

int ApplicationClass::GetClientHeight()
{
	return mClientHeight;
}

HWND ApplicationClass::GetHWnd()
{
	return mHWnd;
}

bool ApplicationClass::IsFullScreen()
{
	return mFullscreen;
}


LRESULT CALLBACK ApplicationClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	InputClass* i = SystemClass::GetInstance()->mInput;
	switch (umsg)
	{
	case WM_ACTIVATE:
		if (LOWORD(wparam) == WA_INACTIVE)
		{
			mAppPaused = true;
			mTimer->Stop();
		}
		else
		{
			mAppPaused = false;
			mTimer->Start();
		}
		return 0;
	case WM_ENTERSIZEMOVE:
		mAppPaused = true;
		mResizing = true;
		mTimer->Stop();
		return 0;
	case WM_EXITSIZEMOVE:
		mAppPaused = false;
		mResizing = false;
		mTimer->Start();
		return 0;
	case WM_MENUCHAR:
		return MAKELRESULT(0, MNC_CLOSE);
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lparam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lparam)->ptMinTrackSize.y = 200;
		return 0;

		// Check if a key has been pressed on the keyboard.
	case WM_KEYDOWN:
	{
		// If a key is pressed send it to the input object so it can record that state.
		i->KeyDown((unsigned int)wparam);
		return 0;
	}

		// Check if a key has been released on the keyboard.
	case WM_KEYUP:
	{
		// If a key is released then send it to the input object so it can unset the state for that key.
		i->KeyUp((unsigned int)wparam);
		return 0;
	}
		// Check if a key on the mouse has been pressed.
	case WM_LBUTTONDOWN:
	{
		i->MouseDown(LMOUSE);
		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		i->MouseDown(MMOUSE);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		i->MouseDown(RMOUSE);
		return 0;
	}
		// Check if a key on the mouse has been released.
	case WM_LBUTTONUP:
	{
		i->MouseUp(LMOUSE);
		return 0;
	}
	case WM_MBUTTONUP:
	{
		i->MouseUp(MMOUSE);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		i->MouseUp(RMOUSE);
		return 0;
	}
		// Check if mouse has been moved.
	case WM_MOUSEMOVE:
	{
		i->OnMouseMove(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		return 0;
	}
		// Check if mouse scroll is used
	case WM_MOUSEWHEEL:
	{
		i->OnMouseScroll(GET_WHEEL_DELTA_WPARAM(wparam));
		return 0;
	}
		// Any other messages send to the default message handler as our application won't make use of them.
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

		// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

		// All other messages pass to the message handler in the system class.
	default:
	{
		return SystemClass::GetInstance()->mAppInst->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}
