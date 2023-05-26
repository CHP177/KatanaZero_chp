#pragma once

class Scene01 : public IScene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() {};
	void Render() override;
	void PostRender() {};

private:
	map<string, unique_ptr<AnimationRect>> texture;
	
};
