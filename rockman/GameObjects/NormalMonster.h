#pragma once
#include "Monster.h"

class NormalMonster : public Monster
{
protected:
	int type;

	bool isAttack = false;

	float delay = 0.f;

public:
	NormalMonster(const std::string& textureId, const std::string& n);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	
	void TurnToPlayer();
};

