#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define TANK_WIDTH		24
#define TANK_HEIGHT		16
#define TANK_ANI_ID 10000

#define TANK_MOVE_SPEED 0.08f

#define TANK_FIRE_CD 400

class CBullet;

class CTank : public CGameObject
{
public:
	enum class TankState {
		Idle,
		MoveUp,
		MoveRight,
		MoveDown,
		MoveLeft
	};
	int GetAnimationId();
	int GetFacing();
	CTank(float x, float y) : CGameObject(x, y) {}
	void GetSize(float& w, float& h) { w = TANK_WIDTH; h = TANK_HEIGHT; }

	void Update(DWORD dt);
	void Render();

	void SetState(TankState newState);

	CBullet* Fire();

private:
	enum class Facing {
		Up,
		Right,
		Down,
		Left
	};
	Facing lastFacing = Facing::Up;
	TankState currentState = TankState::Idle;
	ULONGLONG lastTimeFire = -100;
};
