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

TextureRect::TextureRect(const wstring& texturePath, float ratio)
	: Drawable("TextureRect", Vector2(), Vector2(), 0.0f, L"_Shaders/VertexTexture.hlsl")
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

	SetScale(GetComponent<TextureComponent>("Texture")->GetImageSize() * ratio);
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
	string objName = name + to_string(ordinal);
	string imgName = "Image : " + String::ToString(Path::GetFileName(GetComponent<TextureComponent>("Texture")->GetPath()));
	string shaderName = "Shader : " + String::ToString(Path::GetFileName(shaderPath));

	if (ImGui::BeginMenu(objName.c_str()))
	{
		GetComponent<SelectionComponent>("Selection")->SetOutline(true);

		ImGui::Text(objName.c_str());
		ImGui::Text(imgName.c_str());
		ImGui::Text(shaderName.c_str());

		if (ImGui::Button("ChangeImage", ImVec2(100, 25)))
			ChangeImageFunc();
		if (ImGui::Button("ChangeShader", ImVec2(100, 25)))
			ChangeShaderFunc();

		SUPER::GUI();

		ImGui::EndMenu();
	}
	else
		GetComponent<SelectionComponent>("Selection")->SetOutline(false);
}

void TextureRect::ChangeImageFunc(const wstring& path)
{
	if (path.empty())
	{
		function<void(wstring)> func = bind(&TextureRect::ChangeImageFunc, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::ImageFilter, L"_Textures/", func, gHandle);
	}
	else
		GetComponent<TextureComponent>("Texture")->SetSRV(path);
}

void TextureRect::ChangeShaderFunc(const wstring& path)
{
	if (path.empty())
	{
		function<void(wstring)> func = bind(&TextureRect::ChangeShaderFunc, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::ShaderFilter, L"_Shaders/", func, gHandle);
	}
	else
		SetShader(path);
}

void TextureRect::SaveTextAsFile(const string& text, const wstring& path)
{
	if (path.empty())
	{
		function<void(wstring)> func = bind(&TextureRect::SaveTextAsFile, this, text, placeholders::_1);
		Path::SaveFileDialog(L"", Path::TextFilter, L"./", func, gHandle);
	}
	else
	{
		ofstream writeFile(path.c_str());
		if (writeFile.is_open())
		{
			writeFile << text << '\n';
			writeFile.clear();
		}
		writeFile.close();
	}
}
