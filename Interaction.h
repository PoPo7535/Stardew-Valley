#pragma once
#include"GameObject.h"
class Interaction : public GameObject
{

public:
	virtual bool InteractionPick(int damage) { return false; }
	virtual bool InteractionSword(int damage) { return false; };
	virtual void InteractionAction() {};
	Interaction() {};
	virtual ~Interaction() = default;
};