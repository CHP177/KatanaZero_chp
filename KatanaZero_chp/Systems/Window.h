#pragma once

struct WinDesc
{
	wstring appName = L"";
	HINSTANCE instance = nullptr;
	HWND handle = nullptr;
	float width = 0.0f;
	float height = 0.0f;
};

class Window
{
public:
	Window(const WinDesc& desc);
	~Window();

	ATOM MyRegisterClass(WinDesc desc);

	WPARAM Run();

private:
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	WinDesc desc;

	unique_ptr<class Program> program;
};