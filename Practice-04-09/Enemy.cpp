#include "Enemy.h"
#include "Bullet.h"
#include "Game.h"

CEnemy::CEnemy(float x, float y, float bvxMul, float bvyMul) : CGameObject(x, y) 
{
	this->vx = ENEMY_MOVE_SPEED * bvxMul;
	this->vy = ENEMY_MOVE_SPEED * bvyMul;
}

bool CEnemy::IsDeath() {
	return currentState == EnemyState::Death;
}

void CEnemy::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if (x < 0)
		SetState(EnemyState::Death);
}

int CEnemy::GetAnimationId() {
	return ENEMY_ANI_ID;
}
void CEnemy::Render()
{
	CAnimations::GetInstance()->Get(GetAnimationId())->Render(x, y);
}

void CEnemy::SetState(EnemyState newState)
{
	switch (newState)
	{
	case CEnemy::EnemyState::Death:
		break;
	case CEnemy::EnemyState::MoveDown:
		vx = 0;
		vy = ENEMY_MOVE_SPEED;
		break;
	case CEnemy::EnemyState::MoveLeft:
		vx = -ENEMY_MOVE_SPEED;
		vy = 0;
		break;
	default:
		vx = 0;
		vy = 0;
		break;
	}

	currentState = newState;
}