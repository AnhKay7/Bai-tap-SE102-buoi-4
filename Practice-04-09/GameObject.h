#pragma once

#include <Windows.h>
#include <vector>

using namespace std;

class CGameObject
{
protected:
	float x;
	float y;

	float vx;
	float vy;

	int state;
public:
	CGameObject();
	CGameObject(float x, float y);

	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }

	virtual void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }

	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

	virtual ~CGameObject();

	virtual void GetSize(float& w, float& h) { w = 0; h = 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		float w, h; GetSize(w, h);
		l = x - w / 2; r = x + w / 2;
		t = y - h / 2; b = y + h / 2;
	}
	static bool Overlap(CGameObject* a, CGameObject* b);
};

typedef CGameObject* LPGAMEOBJECT;
