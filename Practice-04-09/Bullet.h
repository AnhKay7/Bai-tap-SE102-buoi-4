#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define BULLET_WIDTH	24
#define BULLET_HEIGHT	10
#define BULLET_SPEED	0.3f
#define BULLET_ANI_ID 20000

class CBullet : public CGameObject
{
	bool isDeleted;
public:
	CBullet(float x, float y, float vx, float vy);

	void Update(DWORD dt);
	void Render();

	bool IsDeleted() { return isDeleted; }
	void GetSize(float& w, float& h) { w = BULLET_WIDTH; h = BULLET_HEIGHT; }

	void Delete() { isDeleted = true; }
};
