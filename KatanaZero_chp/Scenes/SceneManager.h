#pragma once

class SceneManager
{
	DECLARE_SINGLETON(SceneManager);

public:
	void Init();
	void Destroy();

	void Update();
	void PreRender();
	void Render();
	void PostRender();

private:
	IScene* currentScene;
	IScene* preScene;

};
