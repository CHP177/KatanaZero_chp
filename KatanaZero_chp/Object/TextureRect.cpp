#include "stdafx.h"
#include "TextureRect.h"

TextureRect::TextureRect(const Vector2& position, const Vector2& scale, float rotation, const wstring& texturePath)
	: Drawable("TextureRect", position, scale, rotation, L"_Shaders/VertexTexture.hlsl")
{
	vertices.assign(4, VertexTexture());
	vertices[0].position = Vector2(-0.5f, -0.5f);
	vertices[1].position = Vector2(-0.5f, 0.5f);
	vertices[2].position = Vector2(0.5f, -0.5f);
	vertices[3].position = Vector2(0.5f, 0.5f);
	vertices[0].uv = Vector2(0.0f, 1.0f);
	vertices[1].uv = Vector2(0.0f, 0.0f);
	vertices[2].uv = Vector2(1.0f, 1.0f);
	vertices[3].uv = Vector2(1.0f, 0.0f);

	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);

	indices = { 0, 1, 2, 2, 1, 3 };

	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	IL->Create(VertexTexture::descs.data(), VertexTexture::descs.size(), VS->GetBlob());

	AddComponent(make_shared<TextureComponent>(texturePath));
}

void TextureRect::Update()
{
	SUPER::Update();
}

void TextureRect::Render()
{
	SUPER::Render();

	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DC->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}

void TextureRect::GUI(int ordinal)
{
}

void TextureRect::ChangeImageFunc(const wstring& path)
{
}

void TextureRect::ChangeShaderFunc(const wstring& path)
{
}

void TextureRect::SaveTextAsFile(const string& text, const wstring& path)
{
}
