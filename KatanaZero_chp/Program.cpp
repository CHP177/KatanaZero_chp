#include "stdafx.h"
#include "Scenes/SceneList.h"
#include "Program.h"

Program::Program()
{

}

void Program::Init()
{
	sceneList.push_back(make_shared<testScene>());

	currentScene = sceneList[0];
	currentScene->Init();
}

void Program::Update()
{
	CAMERA->Update();

	currentScene->Update();
}

void Program::PreRender()
{
	currentScene->PreRender();
}

void Program::Render()
{
	currentScene->Render();
}

void Program::PostRender()
{
	currentScene->PostRender();
}
