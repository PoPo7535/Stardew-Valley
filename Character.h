#pragma once
class Character
{
protected:
	float moveSpeed;
	int hp;
public:
	Character() :
		moveSpeed{ 0.0f }, hp{ 0 }{}
	virtual ~Character() = default;
};