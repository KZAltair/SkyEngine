#include <Windows.h>

//Windows entrypoint
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//The name of window class
	const auto wndName = "SkyEngine";

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = nullptr;
	wc.hCursor = nullptr;
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	wc.hInstance = hInstance;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = wndName;
	//register window class
	RegisterClassEx(&wc);

	HWND hwnd = CreateWindowEx(0, wndName, "SkyEngine",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hwnd, SW_SHOW);
	//Infine loop to test all stuff with windows
	//TODO remove or rework this stuff
	while (true);
	return 0;
}