#include "App.h"
#include <sstream>

App::App()
	:
	wnd(800, 600, "SkyEngine v0.1")
{
}

int App::Go()
{
	MSG msg;
	BOOL gResult;

	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		DoFrame();
	}

	//Check if GetMessage call itself broke down
	if (gResult == -1)
	{
		throw SKYENGINE_LAST_EXCEPT();
	}

	//wParam is the value to call PostQuitMessage
	return (int)msg.wParam;
}

void App::DoFrame()
{
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		MessageBox(nullptr, "Key pressed", "Space was pressed.", MB_OK | MB_ICONEXCLAMATION);
	}
	if (wnd.kbd.KeyIsPressed(VK_MENU))
	{
		MessageBox(nullptr, "Alt Pressed", "Key pressed.", MB_OK | MB_ICONEXCLAMATION);
	}
	static int count = 0;
	//do app logic test
	while (!wnd.mouse.isEmpty())
	{
		const auto e = wnd.mouse.Read();

		switch (e.GetType())
		{
		case Mouse::Event::Type::Leave:
			wnd.SetTitle("Gone!");
			break;
		case Mouse::Event::Type::Move:
		{
			std::ostringstream oss;
			oss << "Mouse position: (" << e.GetPosX() << ", " << e.GetPosY() << ")";
			wnd.SetTitle(oss.str());
		}
		break;
		case Mouse::Event::Type::WheelUp:
		{
			count++;
			std::ostringstream oss;
			oss << "Up: (" << count << ")";
			wnd.SetTitle(oss.str());
		}
		break;
		case Mouse::Event::Type::WheelDown:
		{
			count--;
			std::ostringstream oss;
			oss << "Up: (" << count << ")";
			wnd.SetTitle(oss.str());
		}
		break;
		}

	}
}
