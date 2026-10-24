#include "TankKeyHandler.h"

#include "debug.h"
#include "Game.h"

#include "Tank.h"
#include "Bullet.h"

extern CTank* tank;
extern vector<CBullet*> bullets;

void CTankKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] Key: %d pressed\n", KeyCode);
	if (tank == NULL) return;

	if (KeyCode == DIK_SPACE) {
		CBullet* bullet = tank->Fire();
		if (bullet != NULL)
			bullets.push_back(bullet);
	}
}

void CTankKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] Key: %d up\n", KeyCode);
}

void CTankKeyHandler::KeyState(BYTE* states)
{
	if (tank == NULL)
		return;

	CGame* game = CGame::GetInstance();

	if (game->IsKeyDown(DIK_UP)) {
		tank->SetState(CTank::TankState::MoveUp);
	}
	else if (game->IsKeyDown(DIK_RIGHT)) {
		tank->SetState(CTank::TankState::MoveRight);
	}
	else if (game->IsKeyDown(DIK_DOWN)) {
		tank->SetState(CTank::TankState::MoveDown);
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		tank->SetState(CTank::TankState::MoveLeft);
	}
	else tank->SetState(CTank::TankState::Idle);
}
