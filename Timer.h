#pragma once
#include<windows.h>
#include<time.h>
#define FPS 10

struct Timer{
	double currentTime;
	double prevTime;
	double deltaTime;
	double frameRate;
	bool   TimeStep();
	Timer();
};

