#include "Sprites.h"
#include "debug.h"

CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == nullptr)
		__instance = new CSprites();
	return __instance;
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	if (sprites.count(id))
		return;

	CSprite* newSprite = new CSprite(id, left, top, right, bottom, tex);
	
	sprites[id] = newSprite;
}

LPSPRITE CSprites::Get(int id)
{
	if (sprites.count(id))
		return sprites[id];
	DebugOut(L"[ERROR] CSprites::Get: sprite id %d not found\n", id);
	return NULL;
}
