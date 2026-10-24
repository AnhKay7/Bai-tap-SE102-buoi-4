#include "Animation.h"
#include "debug.h"

void CAnimation::Add(int spriteId, DWORD time)
{
	LPSPRITE newSprite = CSprites::GetInstance()->Get(spriteId);
	if (newSprite == NULL) {
		DebugOut(L"[ERROR] CAnimation::Add: sprite id %d not found\n", spriteId);
		return;
	}
	CAnimationFrame* newFrame = new CAnimationFrame(newSprite, time == 0 ? defaultTime : time);
	frames.push_back(newFrame);
}

void CAnimation::Render(float x, float y)
{
	if (frames.empty())
		return;

	ULONGLONG now = GetTickCount64();
	if (currentFrame == -1) {
		currentFrame = 0;
		lastFrameTime = now;
	}
	ULONGLONG dt = now - lastFrameTime;
	if (dt >= frames[currentFrame]->GetTime()) {
		currentFrame = (currentFrame + 1) % frames.size();
		lastFrameTime = now;
	}

	frames[currentFrame]->GetSprite()->Draw(x, y);
}
