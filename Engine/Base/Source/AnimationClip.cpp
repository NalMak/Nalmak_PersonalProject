#include "AnimationClip.h"

AnimationClip::AnimationClip()
{
}

AnimationClip::~AnimationClip()
{
	Release();
}

void AnimationClip::Release()
{
	for (auto& transition : transtionInfos)
	{
		SAFE_DELETE(transition);
	}
}
