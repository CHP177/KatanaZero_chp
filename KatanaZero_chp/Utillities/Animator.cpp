#include "stdafx.h"
#include "Animator.h"

AnimationClip::AnimationClip(const wstring& clipName, const ScratchImage& srcTex, UINT frameCount, const Vector2& startPos, const Vector2& endPos, bool bReverse, bool bLoop, float playRate)
	: clipName(clipName), frameCount(frameCount), bReverse(bReverse), bLoop(bLoop), playRate(playRate)
{
	const float& imageWidth = (float)srcTex.GetMetadata().width;
	const float& imageHeight = (float)srcTex.GetMetadata().height;

	Vector2 clipSize = Vector2(abs(endPos.x - startPos.x), abs(endPos.y - startPos.y));
	frameSize = Vector2(clipSize.x / frameCount, clipSize.y);

	Vector2 texelSize = Vector2(1.0f / imageWidth, 1.0f / imageHeight);
	Vector2 texelStartPos = startPos * texelSize;
	texelFrameSize = frameSize * texelSize;

	keyframes.assign(frameCount, Vector2());

	for (UINT i = 0; i < keyframes.size(); ++i)
	{
		keyframes[i].x = texelStartPos.x + texelFrameSize.x * i;
		keyframes[i].y = texelStartPos.y;
	}
}

Animator::Animator(const shared_ptr<AnimationClip>& animClip)
	: currentAnimClip(animClip)
{
	animClips.emplace(animClip->GetClipName(), animClip);
}

Animator::Animator(const vector<shared_ptr<AnimationClip>>& animClips)
	: currentAnimClip(animClips[0])
{
	for (const auto& animClip : animClips)
		this->animClips.emplace(animClip->GetClipName(), animClip);
}

void Animator::Update()
{
	if (bStop) return;

	if (deltaTime > currentAnimClip->GetPlayRate())
	{
		if (currentAnimClip->GetIsReverse() == false) //foward
		{
			currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex);

			++currentFrameIndex;

			if (currentFrameIndex >= currentAnimClip->GetFrameCount())
			{
				if (currentAnimClip->GetIsLoop())
					currentFrameIndex = 0;
				else
					currentFrameIndex = currentAnimClip->GetLastFrameIndex();
			}
		}
		else //reverse
		{
			currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex);

			--currentFrameIndex;

			if (currentFrameIndex == UINT_MAX)
			{
				if (currentAnimClip->GetIsLoop())
					currentFrameIndex = currentAnimClip->GetLastFrameIndex();
				else
					currentFrameIndex = 0;
			}
		}

		deltaTime = 0.0f;
	}

	deltaTime += TIME->GetDeltaTime();
}

void Animator::AddAnimClip(const shared_ptr<AnimationClip>& animClip)
{
	animClips.emplace(animClip->GetClipName(), animClip);
}

void Animator::SetCurrentAnimClip(const wstring& clipName)
{
	if (clipName == currentAnimClip->GetClipName() && currentAnimClip->GetIsLoop() == true) return;

	const auto& iter = animClips.find(clipName);

	if (iter != animClips.end())
	{
		currentAnimClip = iter->second;

		deltaTime = 0.0f;

		if (currentAnimClip->GetIsReverse())
			currentFrameIndex = currentAnimClip->GetLastFrameIndex();
		else
			currentFrameIndex = 0;

		currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex);
	}
}
