#include "Bullet.h"
#include "Game.h"

CBullet::CBullet(float x, float y, float vx, float vy) : CGameObject(x, y)
{
	this->vx = vx * BULLET_SPEED;
	this->vy = vy * BULLET_SPEED;
	isDeleted = false;
}

void CBullet::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	CGame* game = CGame::GetInstance();
	if (x < 0 || x > game->GetBackBufferWidth())
		isDeleted = true;
	if (y < 0 || y > game->GetBackBufferHeight())
		isDeleted = true;
}

void CBullet::Render()
{
	CAnimations::GetInstance()->Get(BULLET_ANI_ID)->Render(x, y);
}
