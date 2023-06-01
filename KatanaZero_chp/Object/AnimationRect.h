#pragma once

class AnimationRect : public TextureRect
{
public:
	AnimationRect(const Vector2& position, const Vector2& scale, float rotation, const wstring& texturePath = L"");
	AnimationRect(const wstring& texturePath = L"", float ratio = 1.0f);

	virtual void Update() override;
	virtual void Render() override;

	auto GetAnimator() const { return animator; }
	auto GetAnimClips() const { return animClips; }

	void SetAnimator(const shared_ptr<Animator>& animator) { this->animator = animator; }
	void AddAnimClip(const shared_ptr<AnimationClip>& animClip) { animClips.push_back(animClip); }

	void SetCurrentAnimClip(const wstring key);

private:
	shared_ptr<Animator> animator;
	vector<shared_ptr<AnimationClip>> animClips;
};
