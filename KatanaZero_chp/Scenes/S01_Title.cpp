#include "stdafx.h"
#include "S01_Title.h"

void Scene01::Init()
{
	speedStruct speed;
	texture.emplace("background", make_unique<TextureRect>(L"_Sprite/Title/background.png", 2.0f));
	texture["background"]->SetPosition(Vector2(CENTER_X, CENTER_Y + 50.0f));
	
	speed = { 600.0f, 20.0f, -160.0f, 10.0f };
	speedMap.emplace("background", speed);
	
	texture.emplace("fence", make_unique<TextureRect>(L"_Sprite/Title/fence.png", 2.0f));
	texture["fence"]->SetPosition(Vector2(CENTER_X, CENTER_Y - 100.0f));

	speed = { 800.0f, 30.0f, -180.0f, 10.0f };
	speedMap.emplace("fence", speed);

	texture.emplace("title", make_unique<TextureRect>(L"_Sprite/Title/titlegraphic_0.png", 1.5f));
	texture["title"]->SetPosition(Vector2(CENTER_X, -200.0f)); //endPosY = CENTER_Y + 45.0f

	texture.emplace("title_1", make_unique<TextureRect>(L"_Sprite/Title/titlegraphic_1.png", 1.5f));
	texture["title_1"]->SetPosition(Vector2(texture["title"]->GetLeft() + texture["title_1"]->GetScale().x / 2.0f - 12.0f, texture["title"]->GetPosition().y));

	texture.emplace("title_2", make_unique<TextureRect>(L"_Sprite/Title/titlegraphic_2.png", 1.5f));
	texture["title_2"]->SetPosition(Vector2(texture["title"]->GetRight() - texture["title_2"]->GetScale().x / 2.0f + 15.0f, texture["title"]->GetPosition().y + 5.0f));

	texture.emplace("title_3", make_unique<TextureRect>(L"_Sprite/Title/titlegraphic_3.png", 1.5f));
	texture["title_3"]->SetPosition(Vector2(texture["title"]->GetPosition().x + 4.0f, texture["title"]->GetTop() - 17.0f));

	speed = { 1000.0f, 60.0f, CENTER_Y - 100.0f, 10.0f };
	speedMap.emplace("title", speed);

	texture.emplace("grass", make_unique<TextureRect>(L"_Sprite/Title/grass.png", 2.0f));
	texture["grass"]->SetPosition(Vector2(CENTER_X, texture["grass"]->GetScale().y / 4.0f));

	animation.emplace("plants", make_unique<AnimationRect>(L"_Sprite/Title/plants.png", 2.0f));
	animation["plants"]->SetPosition(Vector2(CENTER_X, animation["plants"]->GetScale().y / 2.0f - 15.0f));
	animation["plants"]->AddAnimClip(make_shared<AnimationClip>(L"plants", *animation["plants"]->GetComponent<TextureComponent>("Texture")->GetImage(), 12, Vector2(0, 0), animation["plants"]->GetComponent<TextureComponent>("Texture")->GetImageSize(), false, true, 1.0f / 12.0f));
	animation["plants"]->SetAnimator(make_shared<Animator>(animation["plants"]->GetAnimClips()));

	
}

void Scene01::Destroy()
{
	for (auto& tex : texture)
		tex.second.reset();
	for (auto& anim: animation)
		anim.second.reset();
}

void Scene01::Update()
{
	MoveTitle(texture["background"], -10.0f, speedMap["background"]);
	MoveTitle(texture["fence"], 0.0f, speedMap["fence"]);
	MoveTitle(texture["title"], CENTER_Y + 45.0f - texture["title"]->GetScale().y / 2, speedMap["title"]);
	MoveTitle(texture["title_1"], CENTER_Y + 45.0f - texture["title_1"]->GetScale().y / 2, speedMap["title"]);
	MoveTitle(texture["title_2"], CENTER_Y + 47.0f - texture["title_2"]->GetScale().y / 2, speedMap["title"]);
	MoveTitle(texture["title_3"], texture["title"]->GetTop() - texture["title_3"]->GetScale().y / 2.0f - 17.0f, speedMap["title"]);


	animation["plants"]->SetCurrentAnimClip(L"plants");

	for (auto& tex : texture)
		tex.second->Update();
	for (auto& anim : animation)
		anim.second->Update();
}

void Scene01::Render()
{
	//texture["background"]->Render();
	//texture["fence"]->Render();
	//texture["title"]->Render();
	//texture["title_1"]->Render();
	//texture["title_2"]->Render();
	//texture["title_3"]->Render();
	//texture["grass"]->Render();

	for (auto& tex : texture)
		tex.second->Render();
	for (auto& anim : animation)
		anim.second->Render();
}
