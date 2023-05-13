#pragma once

class TextureRect : public Drawable
{
public:
	TextureRect(const Vector2& position, const Vector2& scale, float rotation, const wstring& texturePath = L"");

public:
	void Update() override;
	void Render() override;
	void GUI(int ordinal);

public:
	void ChangeImageFunc(const wstring& path = L"");
	void ChangeShaderFunc(const wstring& path = L"");
	void SaveTextAsFile(const string& text, const wstring& path = L"");

protected:
	vector<VertexTexture> vertices;
	vector<UINT> indices;

};