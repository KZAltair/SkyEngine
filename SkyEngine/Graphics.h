#pragma once
#include "WindowManager.h"
#include <d3d11.h>

class Graphics
{
public:
	Graphics(HWND hwnd);
	Graphics(const Graphics&) = delete; //No need to copy graphics. Do not support those operations
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
};
