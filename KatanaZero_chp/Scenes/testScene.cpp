#include "stdafx.h"
#include "testScene.h"

void testScene::Init()
{
	rect = make_unique<LineRect>(Vector2(CENTER_X, 20.0f), Vector2(1280.0f, 40.0f), 0.0f, WHITE);

	idle = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/Zero/idle.png");
	idleToWalk = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/Zero/idle_to_walk.png");
	walk = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/Zero/walk.png");
	idleToRun = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/Zero/idle_to_run.png");
	run = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/Zero/run.png");
	attack = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/Zero/attack.png");
	doorbreak = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/Zero/doorbreak.png");
	roll = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/Zero/roll.png");
	fall = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/Zero/fall.png");
	jump = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/Zero/jump.png");
	flip = make_unique<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Sprite/Zero/flip.png");

	ScratchImage* image = idle->GetComponent<TextureComponent>("Texture")->GetImage();

	idle->SetPosition(Vector2(100.0f, rect->GetTop() + image->GetMetadata().height / 2.0f));
	idle->AddAnimClip(make_shared<AnimationClip>(L"IdleR", *image, 11, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	idle->AddAnimClip(make_shared<AnimationClip>(L"IdleL", *image, 11, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	idle->SetAnimator(make_shared<Animator>(idle->GetAnimClips()));

	image = idleToWalk->GetComponent<TextureComponent>("Texture")->GetImage();

	idleToWalk->SetPosition(Vector2(200.0f, rect->GetTop() + image->GetMetadata().height / 2.0f));
	idleToWalk->AddAnimClip(make_shared<AnimationClip>(L"IdleToWalkR", *image, 4, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	idleToWalk->AddAnimClip(make_shared<AnimationClip>(L"IdleToWalkL", *image, 4, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	idleToWalk->SetAnimator(make_shared<Animator>(idleToWalk->GetAnimClips()));

	image = walk->GetComponent<TextureComponent>("Texture")->GetImage();

	walk->SetPosition(Vector2(300.0f, rect->GetTop() + image->GetMetadata().height / 2.0f));
	walk->AddAnimClip(make_shared<AnimationClip>(L"WalkR", *image, 10, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	walk->AddAnimClip(make_shared<AnimationClip>(L"WalkL", *image, 10, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	walk->SetAnimator(make_shared<Animator>(walk->GetAnimClips()));

	image = idleToRun->GetComponent<TextureComponent>("Texture")->GetImage();

	idleToRun->SetPosition(Vector2(400.0f, rect->GetTop() + image->GetMetadata().height / 2.0f));
	idleToRun->AddAnimClip(make_shared<AnimationClip>(L"IdleToRunR", *image, 4, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	idleToRun->AddAnimClip(make_shared<AnimationClip>(L"IdleToRunL", *image, 4, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	idleToRun->SetAnimator(make_shared<Animator>(idleToRun->GetAnimClips()));

	image = run->GetComponent<TextureComponent>("Texture")->GetImage();

	run->SetPosition(Vector2(500.0f, rect->GetTop() + image->GetMetadata().height / 2.0f));
	run->AddAnimClip(make_shared<AnimationClip>(L"RunR", *image, 10, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	run->AddAnimClip(make_shared<AnimationClip>(L"RunL", *image, 10, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	run->SetAnimator(make_shared<Animator>(run->GetAnimClips()));

	image = attack->GetComponent<TextureComponent>("Texture")->GetImage();

	attack->SetPosition(Vector2(600.0f, rect->GetTop() + image->GetMetadata().height / 2.0f));
	attack->AddAnimClip(make_shared<AnimationClip>(L"AttackR", *image, 7, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	attack->AddAnimClip(make_shared<AnimationClip>(L"AttackL", *image, 7, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	attack->SetAnimator(make_shared<Animator>(attack->GetAnimClips()));

	image = doorbreak->GetComponent<TextureComponent>("Texture")->GetImage();

	doorbreak->SetPosition(Vector2(700.0f, rect->GetTop() + image->GetMetadata().height / 2.0f));
	doorbreak->AddAnimClip(make_shared<AnimationClip>(L"DoorbreakR", *image, 10, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	doorbreak->AddAnimClip(make_shared<AnimationClip>(L"DoorbreakL", *image, 10, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	doorbreak->SetAnimator(make_shared<Animator>(doorbreak->GetAnimClips()));

	image = roll->GetComponent<TextureComponent>("Texture")->GetImage();

	roll->SetPosition(Vector2(800.0f, rect->GetTop() + image->GetMetadata().height / 2.0f));
	roll->AddAnimClip(make_shared<AnimationClip>(L"RollR", *image, 7, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	roll->AddAnimClip(make_shared<AnimationClip>(L"RollL", *image, 7, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	roll->SetAnimator(make_shared<Animator>(roll->GetAnimClips()));

	image = fall->GetComponent<TextureComponent>("Texture")->GetImage();

	fall->SetPosition(Vector2(900.0f, rect->GetTop() + image->GetMetadata().height / 2.0f));
	fall->AddAnimClip(make_shared<AnimationClip>(L"FallR", *image, 4, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	fall->AddAnimClip(make_shared<AnimationClip>(L"FallL", *image, 4, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	fall->SetAnimator(make_shared<Animator>(fall->GetAnimClips()));

	image = jump->GetComponent<TextureComponent>("Texture")->GetImage();

	jump->SetPosition(Vector2(1000.0f, rect->GetTop() + image->GetMetadata().height / 2.0f));
	jump->AddAnimClip(make_shared<AnimationClip>(L"JumpR", *image, 4, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	jump->AddAnimClip(make_shared<AnimationClip>(L"JumpL", *image, 4, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	jump->SetAnimator(make_shared<Animator>(jump->GetAnimClips()));

	image = flip->GetComponent<TextureComponent>("Texture")->GetImage();

	flip->SetPosition(Vector2(1100.0f, rect->GetTop() + image->GetMetadata().height / 2.0f));
	flip->AddAnimClip(make_shared<AnimationClip>(L"FlipR", *image, 11, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2.0f), false, true, 1.0f / 10.2f));
	flip->AddAnimClip(make_shared<AnimationClip>(L"FlipL", *image, 11, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true, true, PLAYRATE));
	flip->SetAnimator(make_shared<Animator>(flip->GetAnimClips()));

}

void testScene::Destroy()
{
	rect.reset();
	idle.reset();
	idleToWalk.reset();
	walk.reset();
	idleToRun.reset();
	run.reset();
	attack.reset();
	doorbreak.reset();
	roll.reset();
	fall.reset();
	jump.reset();
	flip.reset();
}

void testScene::Update()
{
	if (INPUT->Press('A'))
	{
		idle->SetCurrentAnimClip(L"IdleL");
		idleToWalk->SetCurrentAnimClip(L"IdleToWalkL");
		walk->SetCurrentAnimClip(L"WalkL");
		idleToRun->SetCurrentAnimClip(L"IdleToRunL");
		run->SetCurrentAnimClip(L"RunL");
		attack->SetCurrentAnimClip(L"AttackL");
		doorbreak->SetCurrentAnimClip(L"DoorbreakL");
		roll->SetCurrentAnimClip(L"RollL");
		fall->SetCurrentAnimClip(L"FallL");
		jump->SetCurrentAnimClip(L"JumpL");
		flip->SetCurrentAnimClip(L"FlipL");
	}
	if (INPUT->Press('D'))
	{
		idle->SetCurrentAnimClip(L"IdleR");
		idleToWalk->SetCurrentAnimClip(L"IdleToWalkR");
		walk->SetCurrentAnimClip(L"WalkR");
		idleToRun->SetCurrentAnimClip(L"IdleToRunR");
		run->SetCurrentAnimClip(L"RunR");
		attack->SetCurrentAnimClip(L"AttackR");
		doorbreak->SetCurrentAnimClip(L"DoorbreakR");
		roll->SetCurrentAnimClip(L"RollR");
		fall->SetCurrentAnimClip(L"FallR");
		jump->SetCurrentAnimClip(L"JumpR");
		flip->SetCurrentAnimClip(L"FlipR");
	}

	rect->Update();
	idle->Update();
	idleToWalk->Update();
	walk->Update();
	idleToRun->Update();
	run->Update();
	attack->Update();
	doorbreak->Update();
	roll->Update();
	fall->Update();
	jump->Update();
	flip->Update();
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
	idleToRun->Render();
	run->Render();
	attack->Render();
	doorbreak->Render();
	roll->Render();
	fall->Render();
	jump->Render();
	flip->Render();
}

void testScene::PostRender()
{
}
