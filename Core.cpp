#include "Core.h"

Program::Program(){
	title = "Ung dung giai bai tap toan cao cap";
	DrawString(7, 2, green, title);
	mode = 0;
	exitApp = false;
	timer = new Timer;
	selectMode = new SelectMode;
}

Program::~Program(){
		
}

void Program::Input(){
	selectMode->Input();
}

void Program::Update(){
	selectMode->Update();
}

void Program::Render(){
	selectMode->Render();
}

void Program::Execute(){
	while(exitApp == false){
		if(timer->TimeStep()){
			Input();
			Update();
			Render();
		}
	}
}
