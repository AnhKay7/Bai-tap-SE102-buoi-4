#pragma once

#include "Texture.h"
#include "Game.h"

class CSprite
{
	int id;

	int left;
	int top;
	int right;
	int bottom;

	LPTEXTURE texture;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex);

	void Draw(float x, float y);
};

typedef CSprite* LPSPRITE;
