#include "Sprite.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	this->texture = tex;
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

void CSprite::Draw(float x, float y)
{

	CGame::GetInstance()->Draw(x, y, texture, left, top, right, bottom);
}
