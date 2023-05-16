#pragma once

class testScene : public IScene
{
public:
	void Init() override;
	void Destroy() override;
	
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	//unique_ptr<AnimationRect> player;
	unique_ptr<LineRect> rect;

};
