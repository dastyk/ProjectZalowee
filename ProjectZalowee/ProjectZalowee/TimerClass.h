#ifndef _TIMERCLASS_H_
#define _TIMERCLASS_H_

#pragma once


//////////////
// INCLUDES //
//////////////
#include <windows.h>


class TimerClass
{
public:
	TimerClass();
	~TimerClass();

	float DeltaTime()const;
	float TotalTime()const;

	void Reset();
	void Start();
	void Stop();
	void Tick();

private:
	double mSecondsPerCount, mDeltaTime;
	__int64 mBaseTime, mPausedTime, mStopTime, mPrevTime, mCurrTime;

	bool mStopped;
};

#endif
