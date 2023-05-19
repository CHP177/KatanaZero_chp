#include "stdafx.h"
#include "LineRect.h"

LineRect::LineRect(const Vector2& position, const Vector2& scale, float rotation, const Color& color)
	: Drawable("LineRect", position, scale, rotation, L"_Shaders/Vertex.hlsl"), color(color)
{
	//Local Vertex Info
	vertices.assign(4, VertexColor());
	vertices[0].position = { -0.5f, -0.5f };
	vertices[1].position = { -0.5f, 0.5f };
	vertices[2].position = { 0.5f, 0.5f };
	vertices[3].position = { 0.5f, -0.5f };

	//Index Info
	indices = { 0, 1, 1, 2, 2, 3, 3, 0 };

	//Rendering Pipe Line
	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);
	IL->Create(VertexColor::descs.data(), VertexColor::descs.size(), VS->GetBlob());

	//Component
	AddComponent(make_shared<ColorComponent>(color, 0));
}

void LineRect::Update()
{
	SUPER::Update();
}

void LineRect::Render()
{
	SUPER::Render();
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}
