#include "GameObject.h"

CGameObject::CGameObject()
{
	x = 0;
	y = 0;

	vx = 0;
	vy = 0;

	state = -1;
}

bool CGameObject::Overlap(CGameObject* a, CGameObject* b) {
	float al, at, ar, ab, bl, bt, br, bb;
	a->GetBoundingBox(al, at, ar, ab);
	b->GetBoundingBox(bl, bt, br, bb);
	return al < br && ar > bl && at < bb && ab > bt;
}

CGameObject::CGameObject(float x, float y) : CGameObject()
{
	this->x = x;
	this->y = y;
}

CGameObject::~CGameObject()
{
}
