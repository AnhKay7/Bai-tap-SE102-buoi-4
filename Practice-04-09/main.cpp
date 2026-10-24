#include <windows.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Sprite.h"
#include "Sprites.h"
#include "Animation.h"
#include "Animations.h"

#include "Tank.h"
#include "Bullet.h"
#include "Enemy.h"
#include "TankKeyHandler.h"

#define WINDOW_CLASS_NAME L"PracticeWindow"
#define MAIN_WINDOW_TITLE L"Practice 04-09"
#define WINDOW_ICON_PATH L"tank.ico"

#define BACKGROUND_COLOR D3DXCOLOR(40.0f/255, 40.0f/255, 40.0f/255, 0.0f)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_TANK 0

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_TANK TEXTURES_DIR "\\LifeForce.png"

#define TANK_SPRITE_ID 10000
#define ENEMY_SPRITE_ID 40000
#define BULLET_SPRITE_ID 20000

CTank* tank = NULL;
vector<CBullet*> bullets;
vector<CEnemy*> enemys;

ULONGLONG nextEnemySpawn = 0;
int enemysGroupCount = 0;

CTankKeyHandler* keyHandler;

LPTEXTURE texTank = NULL;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void LoadResources()
{
	CTextures* textures = CTextures::GetInstance();
	textures->Add(ID_TEX_TANK, TEXTURE_PATH_TANK);
	texTank = textures->Get(ID_TEX_TANK);

	for (int i = 0; i < 4; i++) {

		int left = 24 + i * 32;
		int top = 8;
		CSprites::GetInstance()->Add(TANK_SPRITE_ID + 10 + i, left, top, left + 24, top + 15, texTank);
	}
	CSprites::GetInstance()->Add(BULLET_SPRITE_ID, 328, 8, 351, 23, texTank);
	CSprites::GetInstance()->Add(ENEMY_SPRITE_ID, 24, 56, 47, 79, texTank);

	CAnimation* Idle = new CAnimation(0);
	Idle->Add(TANK_SPRITE_ID + 10);

	CAnimation* Move = new CAnimation(80);
	Move->Add(TANK_SPRITE_ID + 10);
	Move->Add(TANK_SPRITE_ID + 10 + 1);

	CAnimation* MoveVertical = new CAnimation(80);
	MoveVertical->Add(TANK_SPRITE_ID + 10 + 1);
	MoveVertical->Add(TANK_SPRITE_ID + 12);
	MoveVertical->Add(TANK_SPRITE_ID + 13);

	CAnimations::GetInstance()->Add(TANK_ANI_ID, Idle);
	CAnimations::GetInstance()->Add(TANK_ANI_ID + 1, Move);
	CAnimations::GetInstance()->Add(TANK_ANI_ID + 2, MoveVertical);

	CAnimation* flyingBullet = new CAnimation(0);
	flyingBullet->Add(BULLET_SPRITE_ID);
	CAnimations::GetInstance()->Add(BULLET_ANI_ID, flyingBullet);

	CAnimation* EnemyAni = new CAnimation(0);
	EnemyAni->Add(ENEMY_SPRITE_ID);
	CAnimations::GetInstance()->Add(ENEMY_ANI_ID, EnemyAni);

	tank = new CTank(150.0f, 100.0f);
}
void ProcessCollisions()
{
	for (CBullet* b : bullets) {
		if (b->IsDeleted()) continue;
		for (CEnemy* e : enemys)
		{
			if (e->IsDeath()) continue;
			if (CGameObject::Overlap(b, e)) {
				b->Delete();
				e->SetState(CEnemy::EnemyState::Death);
				break;
			}
		}
	}

	if (tank == NULL) return;
	for (CEnemy* e : enemys) {
		if (e->IsDeath()) continue;
		if (CGameObject::Overlap(tank, e)) {
			e->SetState(CEnemy::EnemyState::Death);
			delete tank;
			tank = NULL;
			return;
		}
	}
}
void Update(DWORD dt)
{

	ProcessCollisions();

	if (tank != NULL)
	{
		tank->Update(dt);
	}
	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size();) {
			bullets[i]->Update(dt);
			if (bullets[i]->IsDeleted()) {
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
			}
			else i++;
		}
	}

	ULONGLONG now = GetTickCount64();
	if (now >= nextEnemySpawn) {

		float x = CGame::GetInstance()->GetBackBufferWidth();
		float y = CGame::GetInstance()->GetBackBufferHeight();

		enemysGroupCount++;

		if (enemysGroupCount < 4) {
			nextEnemySpawn = now + ENEMY_SPAWN_CD;
		}
		else {
			enemysGroupCount = 0;
			nextEnemySpawn = now + ENEMY_GROUP_SPAWN_TIME;
		}

		enemys.push_back(new CEnemy(x, y / 2, -1, 0));
	}
	if (!enemys.empty()) {
		for (int i = 0; i < enemys.size();) {
			enemys[i]->Update(dt);
			if (enemys[i]->IsDeath()) {
				delete enemys[i];
				enemys.erase(enemys.begin() + i);
			}
			else i++;
		}
	}
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

	spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

	if (tank != NULL)
		tank->Render();

	if (!bullets.empty()) {
		for (CBullet* bullet : bullets)
			bullet->Render();
	}

	if (!enemys.empty()) {
		for (CEnemy* enemy : enemys)
			enemy->Render();
	}
	spriteHandler->End();
	pSwapChain->Present(0, 0);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG framestart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();
		ULONGLONG dt = now - framestart;
		if (dt >= tickPerFrame)
		{
			framestart = now;
			Update((DWORD)dt);
			CGame::GetInstance()->ProcessKeyboard();
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	SetDebugWindow(hWnd);

	CGame* game = CGame::GetInstance();
	game->Init(hWnd, hInstance);

	keyHandler = new CTankKeyHandler();
	game->InitKeyboard(keyHandler);

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	LoadResources();

	Run();

	return 0;
}
