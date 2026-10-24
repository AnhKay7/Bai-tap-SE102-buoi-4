#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define ENEMY_WIDTH		24
#define ENEMY_HEIGHT	15
#define ENEMY_ANI_ID 40000

#define ENEMY_MOVE_SPEED 0.1f

#define ENEMY_SPAWN_CD 400
#define ENEMY_GROUP_SPAWN_TIME 4000

class CEnemy : public CGameObject
{
public:
	enum class EnemyState {
		MoveLeft,
		MoveDown,
		Death
	};
	int GetAnimationId();
	int GetFacing();
	CEnemy(float x, float y) : CGameObject(x, y) {}
	CEnemy(float bx, float by, float bvxMul, float bvyMul);
	void Update(DWORD dt);
	void Render();

	void SetState(EnemyState newState);
	bool IsDeath();
	void GetSize(float& w, float& h) { w = ENEMY_WIDTH; h = ENEMY_HEIGHT; }
private:
	int cnt = 0;
	enum class Facing {
		Up,
		Right,
		Down,
		Left
	};
	ULONGLONG lastTimeSpawn = -100;
	EnemyState currentState = EnemyState::MoveLeft;
};

