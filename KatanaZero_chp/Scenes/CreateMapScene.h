#pragma once

class CreateMapScene : public IScene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	unique_ptr<TileMap> tilemap;

};

