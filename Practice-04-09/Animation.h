#pragma once

#include <Windows.h>
#include <vector>

#include "Sprites.h"

using namespace std;

class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;
public:
	CAnimationFrame(LPSPRITE sprite, DWORD time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame* LPANIMATION_FRAME;

class CAnimation
{
	ULONGLONG lastFrameTime;
	DWORD defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(DWORD defaultTime) { this->defaultTime = defaultTime; lastFrameTime = 0; currentFrame = -1; }

	void Add(int spriteId, DWORD time = 0);

	void Render(float x, float y);
};

typedef CAnimation* LPANIMATION;
