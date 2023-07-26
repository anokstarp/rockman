#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"

class Player;

class Monster : public SpriteGo
{
	friend class Stage1_1;

protected:
	int healthPoint;
	int damage;

	Player* player;
	AnimationController animation;

public:
	Monster(const std::string& textureId, const std::string& n);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetPlayer(Player* player);
};

