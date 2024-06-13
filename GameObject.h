#pragma once
#include"stdafx.h"
#include "GameEntity.h"
class Image;
class GameObject : public GameEntity
{
protected:	// 상속된 클래스에 노출시킨다.
	POINTFLOAT pos;
	RECT rect;
	Image* img;
	int bodySize;
public:
	GameObject() :
		pos{},
		rect{},
		bodySize{ NULL },
		img{ nullptr }
	{}

	virtual ~GameObject() = default;
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline float GetPosY() const { return  this->pos.y; }
	inline int GetBodySize() { return this->bodySize; }
	inline RECT GetRect() { return this->rect; }
};
