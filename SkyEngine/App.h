#pragma once
#include "Window.h"

class App
{
public:
	App();
	//Master frame/message loop
	int Go();
private:
	void DoFrame(); //Logic for every frame should be here
private:
	Window wnd;
};
