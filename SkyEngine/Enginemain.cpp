#include "App.h"

//Windows entrypoint
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try {
		return App{}.Go();
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