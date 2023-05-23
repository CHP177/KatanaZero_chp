#pragma once

#define MAX_INPUT_KEY 256

class Input
{
	DECLARE_SINGLETON(Input);

public:
	void Update();

	void InputProc(UINT message, LPARAM lParam);

	bool Down(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_DOWN; }
	bool Up(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_UP; }
	bool Press(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_PRESS; }
	bool DblCkl() { return isDblClk; }

	Vector2 GetMousePosition() { return mousePosition; }

private:
	Vector2 mousePosition;

	array<unsigned char, MAX_INPUT_KEY> keyState = { 0 };
	array<unsigned char, MAX_INPUT_KEY> keyOldState = { 0 };
	array<unsigned char, MAX_INPUT_KEY> keyMap = { 0 };

	bool isDblClk = false;

	enum
	{
		KEY_INPUT_STATUS_NONE = 0,
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_UP,
		KEY_INPUT_STATUS_PRESS,
	};
};