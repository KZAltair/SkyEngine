#include "App.h"
#include <sstream>
#include <iomanip>

App::App()
	:
	wnd(800, 600, "SkyEngine v0.1")
{
}

int App::Go()
{

	while (true)
	{
		//process all messages pending
		if (const auto ecode = Window::ProcessMessages())
		{
			//if return optional has value
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	//const float t = timer.Peek();
	//std::ostringstream oss;
	//oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t << "s";
	//wnd.SetTitle(oss.str());
	//const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(0.0f, 0.0f, 0.0f);
	wnd.Gfx().DrawTestTriangle();
	wnd.Gfx().EndFrame();
}
