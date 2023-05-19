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
	unique_ptr<AnimationRect> idle;
	unique_ptr<AnimationRect> idleToWalk;
	unique_ptr<AnimationRect> walk;
	unique_ptr<AnimationRect> run;
	unique_ptr<AnimationRect> attack;
	unique_ptr<AnimationRect> doorbreak;
	unique_ptr<AnimationRect> roll;
	unique_ptr<LineRect> rect;

};
