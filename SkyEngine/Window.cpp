#include "Window.h"
#include <sstream>
#include "resource.h"

//Window class creation
Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept
	:
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = nullptr;
	wc.hCursor = nullptr;
	wc.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));
	wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
	wc.hInstance = GetInstance();
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	//register window class
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}
const char * Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}

Window::Window(int width, int height, const char * name)
{
	//Calculate window size based on desired client region size
	RECT wr = { 0 };
	wr.left = 100;
	wr.right = width + wr.right;
	wr.top = 100;
	wr.bottom = height + wr.top;
	if (FAILED(AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)))
	{
		throw SKYENGINE_LAST_EXCEPT();
	};

	//Create window and get hWnd
	hWnd = CreateWindow(
		WindowClass::GetName(),
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this);
	//check for error
	if (hWnd == nullptr)
	{
		throw SKYENGINE_LAST_EXCEPT();
	}
	//Show window
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT WINAPI Window::HandleMsgSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		//extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		//set WinAPI managed user data to store ptr to window class
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		//Set wndproc to normal now that setup is finished
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		//forward message to window class handler
		return pWnd->HandleMsg(hwnd, msg, wParam, lParam);

	}
	//if we get message before WM_NCCREATE message, handle with default message
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMsgThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	//retrieve ptr to winodw class
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	return pWnd->HandleMsg(hwnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	//clear state of a key pressed when window loose focus
	case WM_KILLFOCUS:
		kbd.ClearState();
		break;
	//Keyboard messages
	case WM_KEYDOWN:
	//Handle alt key as well
	case WM_SYSKEYDOWN:
		if (!(lParam & 0x40000000) || kbd.AutoRepeatIsEnabled()) //filter if same key was pressed and not released yet
		{
			kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	case WM_KEYUP:
	//Handle alt key as well
	case WM_SYSKEYUP:
		kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		kbd.OnChar(static_cast<unsigned char>(wParam));
		break;
	//End of Keyboard messages
	}


	return DefWindowProc(hwnd, msg, wParam, lParam);
}

Window::Exception::Exception(int line, const char * file, HRESULT hr) noexcept
	:
	ExceptionManager(line, file),
	hr(hr)
{
}

const char * Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code]" << GetErrorCode() << std::endl
		<< "[Description]" << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char * Window::Exception::GetType() const noexcept
{
	return "SkyEngine Exception Manager";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr);
	if (nMsgLen == 0)
	{
		return "Undefined error code.";
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);
	return errorString;
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}
