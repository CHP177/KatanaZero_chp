#include "stdafx.h"
#include "testScene.h"

void testScene::Init()
{
	rect = make_unique<LineRect>(Vector2(CENTER_X, 20.0f), Vector2(1280.0f, 40.0f), 0.0f, WHITE);

	idle = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/idle.png");
	idleToWalk = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/idle_to_walk.png");
	walk = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/walk.png");
	run = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/run.png");
	attack = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/attack.png");
	doorbreak = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/doorbreak.png");
	roll = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/roll.png");

	ScratchImage* image = idle->GetComponent<TextureComponent>("Texture")->GetImage();

	idle->SetScale(Vector2(image->GetMetadata().width / 11.0f, image->GetMetadata().height / 2.0f) * 2.0f);
	idle->SetPosition(Vector2(100.0f, rect->GetTop() + idle->GetScale().y / 2.0f));
	idle->AddAnimClip(make_shared<AnimationClip>(L"IdleR", *image, 11, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	idle->AddAnimClip(make_shared<AnimationClip>(L"IdleL", *image, 11, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	idle->SetAnimator(make_shared<Animator>(idle->GetAnimClips()));

	image = idleToWalk->GetComponent<TextureComponent>("Texture")->GetImage();

	idleToWalk->SetScale(Vector2(image->GetMetadata().width / 4.0f, image->GetMetadata().height / 2.0f) * 2.0f);
	idleToWalk->SetPosition(Vector2(200.0f, rect->GetTop() + idleToWalk->GetScale().y / 2.0f));
	idleToWalk->AddAnimClip(make_shared<AnimationClip>(L"IdleToWalkR", *image, 4, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	idleToWalk->AddAnimClip(make_shared<AnimationClip>(L"IdleToWalkL", *image, 4, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	idleToWalk->SetAnimator(make_shared<Animator>(idleToWalk->GetAnimClips()));

	image = walk->GetComponent<TextureComponent>("Texture")->GetImage();

	walk->SetScale(Vector2(image->GetMetadata().width / 10.0f, image->GetMetadata().height / 2.0f) * 2.0f);
	walk->SetPosition(Vector2(300.0f, rect->GetTop() + walk->GetScale().y / 2.0f));
	walk->AddAnimClip(make_shared<AnimationClip>(L"WalkR", *image, 10, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	walk->AddAnimClip(make_shared<AnimationClip>(L"WalkL", *image, 10, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	walk->SetAnimator(make_shared<Animator>(walk->GetAnimClips()));

	image = run->GetComponent<TextureComponent>("Texture")->GetImage();

	run->SetScale(Vector2(image->GetMetadata().width / 10.0f, image->GetMetadata().height / 2.0f) * 2.0f);
	run->SetPosition(Vector2(400.0f, rect->GetTop() + run->GetScale().y / 2.0f));
	run->AddAnimClip(make_shared<AnimationClip>(L"RunR", *image, 10, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	run->AddAnimClip(make_shared<AnimationClip>(L"RunL", *image, 10, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	run->SetAnimator(make_shared<Animator>(run->GetAnimClips()));

	image = attack->GetComponent<TextureComponent>("Texture")->GetImage();

	attack->SetScale(Vector2(image->GetMetadata().width / 7.0f, image->GetMetadata().height / 2.0f) * 2.0f);
	attack->SetPosition(Vector2(500.0f, rect->GetTop() + attack->GetScale().y / 2.0f));
	attack->AddAnimClip(make_shared<AnimationClip>(L"AttackR", *image, 7, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	attack->AddAnimClip(make_shared<AnimationClip>(L"AttackL", *image, 7, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	attack->SetAnimator(make_shared<Animator>(attack->GetAnimClips()));

	image = doorbreak->GetComponent<TextureComponent>("Texture")->GetImage();

	doorbreak->SetScale(Vector2(image->GetMetadata().width / 10.0f, image->GetMetadata().height / 2.0f) * 2.0f);
	doorbreak->SetPosition(Vector2(600.0f, rect->GetTop() + doorbreak->GetScale().y / 2.0f));
	doorbreak->AddAnimClip(make_shared<AnimationClip>(L"DoorbreakR", *image, 10, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	doorbreak->AddAnimClip(make_shared<AnimationClip>(L"DoorbreakL", *image, 10, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	doorbreak->SetAnimator(make_shared<Animator>(doorbreak->GetAnimClips()));

	image = roll->GetComponent<TextureComponent>("Texture")->GetImage();

	roll->SetScale(Vector2(image->GetMetadata().width / 7.0f, image->GetMetadata().height / 2.0f) * 2.0f);
	roll->SetPosition(Vector2(700.0f, rect->GetTop() + roll->GetScale().y / 2.0f));
	roll->AddAnimClip(make_shared<AnimationClip>(L"RollR", *image, 7, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	roll->AddAnimClip(make_shared<AnimationClip>(L"RollL", *image, 7, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	roll->SetAnimator(make_shared<Animator>(roll->GetAnimClips()));

}

void testScene::Destroy()
{
	rect.reset();
	idle.reset();
	idleToWalk.reset();
	walk.reset();
	run.reset();
	attack.reset();
	doorbreak.reset();
	roll.reset();
}

void testScene::Update()
{
	if (INPUT->Press('A'))
	{
		idle->GetAnimator()->SetCurrentAnimClip(L"IdleL");
		idleToWalk->GetAnimator()->SetCurrentAnimClip(L"IdleToWalkL");
		walk->GetAnimator()->SetCurrentAnimClip(L"WalkL");
		run->GetAnimator()->SetCurrentAnimClip(L"RunL");
		attack->GetAnimator()->SetCurrentAnimClip(L"AttackL");
		doorbreak->GetAnimator()->SetCurrentAnimClip(L"DoorbreakL");
		roll->GetAnimator()->SetCurrentAnimClip(L"RollL");
	}
	if (INPUT->Press('D'))
	{
		idle->GetAnimator()->SetCurrentAnimClip(L"IdleR");
		idleToWalk->GetAnimator()->SetCurrentAnimClip(L"IdleToWalkR");
		walk->GetAnimator()->SetCurrentAnimClip(L"WalkR");
		run->GetAnimator()->SetCurrentAnimClip(L"RunR");
		attack->GetAnimator()->SetCurrentAnimClip(L"AttackR");
		doorbreak->GetAnimator()->SetCurrentAnimClip(L"DoorbreakR");
		roll->GetAnimator()->SetCurrentAnimClip(L"RollR");
	}

	rect->Update();
	idle->Update();
	idleToWalk->Update();
	walk->Update();
	run->Update();
	attack->Update();
	doorbreak->Update();
	roll->Update();
}

void testScene::PreRender()
{
}

void testScene::Render()
{
	rect->Render();
	idle->Render();
	idleToWalk->Render();
	walk->Render();
	run->Render();
	attack->Render();
	doorbreak->Render();
	roll->Render();
}

void testScene::PostRender()
{
}
