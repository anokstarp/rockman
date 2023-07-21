#pragma once
#include "SpriteGo.h"

class Monster : public SpriteGo
{
protected:
	int healthPoint;
	int damage;


public:
	Monster();
	virtual ~Monster();

	void OnHit();

};

