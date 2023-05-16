#include "stdafx.h"
#include "testScene.h"

void testScene::Init()
{
	//player = make_unique<AnimationRect>(Vector2(300.0f, 300.0f), CENTER, 0.0f, L"_Sprite/idle.png");

	//ScratchImage* image = player->GetComponent<TextureComponent>("Texture")->GetImage();

	//player->GetComponent<TextureComponent>("Texture")->SetIsMagenta(true);

	//player->AddAnimClip(make_shared<AnimationClip>(L"Idle", *image, 11, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height)));
	//player->SetAnimator(make_shared<Animator>(player->GetAnimClips()));
	rect = make_unique<LineRect>(CENTER, Vector2(100.0f, 100.0f), 0.0f, RED);
}

void testScene::Destroy()
{
	//player.reset();
}

void testScene::Update()
{
	rect->Update();

	//player->Update();
}

void testScene::PreRender()
{
}

void testScene::Render()
{
	rect->Render();
	//player->Render();
}

void testScene::PostRender()
{
}
