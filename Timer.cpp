#include "timer.h"

Timer::Timer(){
	currentTime = clock();
	frameRate = double(1)/FPS;
}

bool Timer::TimeStep(){
	prevTime    = currentTime;
	currentTime = clock();
	deltaTime  += float(currentTime - prevTime) / CLOCKS_PER_SEC;
	
	if(deltaTime >= frameRate){
		while(deltaTime >= frameRate)
			deltaTime -= frameRate;
		return 1;
	}
	return 0;
}
