#include "stdafx.h"
#include "Drawable.h"

Drawable::Drawable(const string& name, const Vector2 position, const Vector2& scale, float rotation, const wstring& shaderPath)
	: Object(name, position, scale, rotation), shaderPath(shaderPath)
{
	//Input Assembler
	VB = make_unique<VertexBuffer>();
	IB = make_unique<IndexBuffer>();

	//Vertex Shader
	VS = make_unique<VertexShader>();
	VS->Create(shaderPath, "VS");

	IL = make_unique<InputLayout>();

	//Pixel Shader
	PS = make_unique<PixelShader>();
	PS->Create(shaderPath, "PS");
}

void Drawable::SetShader(const wstring& shaderPath)
{
	this->shaderPath = shaderPath;
	VS->Create(shaderPath, "VS");
	PS->Create(shaderPath, "PS");
}

void Drawable::Update()
{
	SUPER::Update();
}

void Drawable::Render()
{
	SUPER::Render();

	//Input Assembler
	VB->SetIA();
	IB->SetIA();
	IL->SetIA();

	//Vertex Shader
	VS->SetShader();

	//Pixel Shader
	PS->SetShader();

	//Draw Call
	DC->DrawIndexed(IB->GetCount(), 0, 0);
}

void Drawable::DrawCall(const D3D11_PRIMITIVE_TOPOLOGY& topology, bool indexed)
{
	DC->IASetPrimitiveTopology(topology);

	if (indexed)
		DC->DrawIndexed(IB->GetCount(), 0, 0);
	else
		DC->Draw(VB->GetCount(), 0);
}
