#pragma once

class Scene01 : public IScene
{
	struct speedStruct
	{
		speedStruct() {}
		speedStruct(float startSpeed, float decreSpeed, float decrePoint, float minimSpeed)
			: startSpeed(startSpeed), decreSpeed(decreSpeed), decrePoint(decrePoint), minimSpeed(minimSpeed) {}

		float startSpeed;
		float decreSpeed;
		float decrePoint;
		float minimSpeed;
	};
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() {};
	void Render() override;
	void PostRender() {};

public:
	void MoveTitle(const unique_ptr<TextureRect>& texture, float endPosY, speedStruct& speed)
	{
		if (texture->GetBottom() < endPosY)
		{
			texture->Move(Vector2(0, speed.startSpeed));

			if (texture->GetBottom() > speed.decrePoint)
			{
				speed.startSpeed -= speed.decreSpeed;
				if (speed.startSpeed <= speed.minimSpeed)
					speed.startSpeed = speed.minimSpeed;
			}

			if (texture->GetBottom() > endPosY)
				texture->SetPosition(Vector2(texture->GetPosition().x, texture->GetScale().y / 2.0f + endPosY));
		}
	}

private:
	map<string, unique_ptr<TextureRect>> texture;
	map<string, unique_ptr<AnimationRect>> animation;
	map<string, speedStruct> speedMap;

};
