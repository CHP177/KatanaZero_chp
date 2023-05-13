#pragma once

class Gui
{
	DECLARE_SINGLETON(Gui);

public:
	LRESULT MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	void Resize();

	void PrintFrame();

public:
	void Update();
	void Render();

	void ObjectListGUIS(vector<shared_ptr<class Object>>& obVec, const char* name);
	void TextureRectGUIS(vector<shared_ptr<class TextureRect>>& trVec, const char* name);

private:
	void ApplyStyle();

};
