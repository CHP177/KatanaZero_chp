#pragma once

class Input
{
	DECLARE_SINGLETON(Input);

public:
	void Update();

	void InputProc(UINT message, LPARAM lParam);

	//bool Down(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_DOWN; }

private:
	
};