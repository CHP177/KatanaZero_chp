#pragma once

class AnimationRect : public TextureRect
{
public:
	AnimationRect(const Vector2& position, const Vector2& scale, float rotation, const wstring& texturePath = L"");

	virtual void Update() override;
	virtual void Render() override;

	auto GetAnimator() const { return animator; }
	auto GetAnimClips() const { return animClips; }

	void SetAnimator(const shared_ptr<Animator>& animator) { this->animator = animator; }
	void AddAnimClip(const shared_ptr<AnimationClip>& animClip) { animClips.push_back(animClip); }

private:
	shared_ptr<Animator> animator;
	vector<shared_ptr<AnimationClip>> animClips;
};
