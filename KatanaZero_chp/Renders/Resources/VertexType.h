#pragma once

struct VertexColor
{
	VertexColor() : VertexColor(Vector2(0, 0), Color(0, 0, 0, 1)) {}
	VertexColor(const Vector2& position, const Color& color)
		: position(position), color(color)
	{}

	Vector2 position;
	Color color;

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

struct VertexTexture
{
	VertexTexture() : VertexTexture(Vector2(0, 0), Vector2(0, 0)) {}
	VertexTexture(const Vector2& position, const Vector2& uv)
		: position(position), uv(uv)
	{}

	Vector2 position;
	Vector2 uv;

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};