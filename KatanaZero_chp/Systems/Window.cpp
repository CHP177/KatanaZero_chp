#include "stdafx.h"
#include "Program.h"
#include "Window.h"

Window::Window(const WinDesc& desc)
	:desc(desc)
{
	WORD wHr = MyRegisterClass(desc);
	assert(wHr != 0);

	this->desc.handle = CreateWindowExW
	(
		WS_EX_APPWINDOW,
		desc.appName.c_str(),
		desc.appName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		(HMENU)nullptr,
		desc.instance,
		nullptr
	);

	RECT rect = { 0, 0, (LONG)this->desc.width, (LONG)this->desc.height };

	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, 0);

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)this->desc.width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)this->desc.height) / 2;

	MoveWindow
	(
		this->desc.handle,
		centerX,
		centerY,
		rect.right - rect.left,
		rect.bottom - rect.top,
		true
	);

	ShowWindow(this->desc.handle, SW_SHOWNORMAL);
	UpdateWindow(this->desc.handle);

	ShowCursor(true);
}

Window::~Window()
{
	DestroyWindow(desc.handle);
	UnregisterClassW(desc.appName.c_str(), desc.instance);
}

ATOM Window::MyRegisterClass(WinDesc desc)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = desc.instance;
	wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = desc.appName.c_str();
	wcex.hIconSm = wcex.hIcon;

	return RegisterClassExW(&wcex);
}

WPARAM Window::Run()
{
	MSG msg;

	program = make_unique<Program>();
	program->Init();

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//Systems
			INPUT->Update();
			TIME->Update();

			//Program
			program->Update();

			GRAPHICS->Begin();
			{
				program->Render();

			}
			GRAPHICS->End();
		}
	}

	return msg.wParam;
}

LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		gHandle = handle;
		break;
	}
	case WM_SIZE:
		gWinWidth = (float)GET_X_LPARAM(lParam);
		gWinHeight = (float)GET_Y_LPARAM(lParam);
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}
