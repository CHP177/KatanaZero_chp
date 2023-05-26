#include "stdafx.h"
#include "S01_Title.h"

void Scene01::Init()
{
	texture.emplace("background", make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/Title/background.png");
	
	Vector2 temp;
	temp = texture["background"]->GetComponent<TextureComponent>("Texture")->GetImageSize();
	float ratio = WIN_DEFAULT_WIDTH / temp.x;
	temp *= ratio;
	texture["background"]->SetScale(temp);
	texture["background"]->SetPosition(Vector2(CENTER_X, texture["background"]->GetScale().y / 2));
}

void Scene01::Destroy()
{
	for (auto& tex : texture)
		tex.second.reset();
}

void Scene01::Update()
{

	for (auto& tex : texture)
		tex.second->Update();
}

void Scene01::Render()
{
	for (auto& tex : texture)
		tex.second->Render();
}
