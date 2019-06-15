#include "Window.h"
#include <sstream>

//Windows entrypoint
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try {
		Window wnd(800, 600, "SkyEngine");

		MSG msg;
		BOOL gResult;

		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (wnd.kbd.KeyIsPressed(VK_SPACE))
			{
				MessageBox(nullptr, "Key pressed", "Space was pressed.", MB_OK | MB_ICONEXCLAMATION);
			}
			if (wnd.kbd.KeyIsPressed(VK_MENU))
			{
				MessageBox(nullptr, "Alt Pressed", "Key pressed.", MB_OK | MB_ICONEXCLAMATION);
			}
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
				}
				
			}
		}
		if (gResult == -1)
		{
			return -1;
		}
		else
		{
			return (int)msg.wParam;
		}
	}
	catch (const ExceptionManager& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No error info available!", "Unknown exception.", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
	
}