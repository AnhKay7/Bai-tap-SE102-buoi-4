#include "Tank.h"
#include "Bullet.h"
#include "Game.h"

void CTank::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	float halfW = TANK_WIDTH / 2.0f;
	float halfH = TANK_HEIGHT / 2.0f;
	if (x < halfW)
		x = halfW;
	float rightEdge = CGame::GetInstance()->GetBackBufferWidth() - halfW;
	if (x > rightEdge)
		x = rightEdge;

	if (y < halfH)
		y = halfH;
	float bottomEdge = CGame::GetInstance()->GetBackBufferHeight() - halfH;
	if (y > bottomEdge)
		y = bottomEdge;
}

int CTank::GetFacing() {
	return (int)lastFacing;
}
int CTank::GetAnimationId() {
	bool moveValue = (currentState != TankState::Idle ? 1 : 0);
	bool moveVerticalValue = (currentState == TankState::MoveUp || currentState == TankState::MoveDown);
	return TANK_ANI_ID + moveValue + moveVerticalValue;
}

void CTank::Render()
{
	CAnimations::GetInstance()->Get(GetAnimationId())->Render(x, y);
}

void CTank::SetState(TankState newState)
{
	switch (newState)
	{
	case CTank::TankState::Idle:
		vx = 0;
		vy = 0;
		break;
	case CTank::TankState::MoveUp:
		lastFacing = Facing::Up;
		vx = 0;
		vy = -TANK_MOVE_SPEED;
		break;
	case CTank::TankState::MoveRight:
		lastFacing = Facing::Right;
		vx = TANK_MOVE_SPEED;
		vy = 0;
		break;
	case CTank::TankState::MoveDown:
		lastFacing = Facing::Down;
		vx = 0;
		vy = TANK_MOVE_SPEED;
		break;
	case CTank::TankState::MoveLeft:
		lastFacing = Facing::Left;
		vx = -TANK_MOVE_SPEED;
		vy = 0;
		break;
	default:
		vx = 0;
		vy = 0;
		break;
	}

	currentState = newState;
}

CBullet* CTank::Fire()
{
	ULONGLONG now = GetTickCount64();
	if (now - lastTimeFire <= TANK_FIRE_CD)
		return NULL;

	lastTimeFire = now;
	float bx = x, by = y;
	float bvxMul = 1, bvyMul = 0;

	return new CBullet(bx, by, bvxMul, bvyMul);
}
