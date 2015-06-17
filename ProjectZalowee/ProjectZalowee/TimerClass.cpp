#include "TimerClass.h"


TimerClass::TimerClass()
{
	mSecondsPerCount = 0.0;
	mDeltaTime = -1.0;
	mBaseTime = 0;
	mPausedTime = 0;
	mPrevTime = 0;
	mCurrTime = 0;
	mStopped = false;
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}


TimerClass::~TimerClass()
{
}

void TimerClass::Tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	// Get current time
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;

	// Get difference between this and previous frame.
	mDeltaTime = (mCurrTime - mPrevTime)*mSecondsPerCount;

	// Update previous time.
	mPrevTime = mCurrTime;

	if (mDeltaTime < 0.0)
		mDeltaTime = 0.0;
}

float TimerClass::DeltaTime()const
{
	return (float)mDeltaTime;
}

void TimerClass::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void TimerClass::Stop()
{
	if (!mStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		mStopTime = currTime;
		mStopped = true;
	}
}

void TimerClass::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (mStopped)
	{
		mPausedTime += startTime - mStopTime;

		mPrevTime = startTime;

		mStopTime = 0;
		mStopped = false;
	}
}

float TimerClass::TotalTime()const
{
	if (mStopped)
		return (float)(((mStopTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
	else
		return (float)(((mCurrTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
}