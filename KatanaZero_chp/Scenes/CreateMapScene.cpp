#include "stdafx.h"
#include "CreateMapScene.h"

void CreateMapScene::Init()
{
	tilemap = make_unique<TileMap>(Vector2(), Vector2(1736.0f, WIN_DEFAULT_HEIGHT), 0.0f, L"_TileSet/TileSet.png", 36);
}

void CreateMapScene::Destroy()
{
	tilemap.reset();
}

void CreateMapScene::Update()
{
	if (INPUT->Down(VK_F8))
		tilemap->SaveTileMapToImageFile(L"_ScreenShots/ScreenShot.jpg");
	tilemap->Update();
}

void CreateMapScene::PreRender()
{
}

void CreateMapScene::Render()
{
	tilemap->Render();
}

void CreateMapScene::PostRender()
{
	tilemap->GUI();
}
