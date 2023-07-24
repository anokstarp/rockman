#pragma once
#include "Monster.h"

class BossMonster : public Monster
{
	float delay;
	float graceTime;

	sf::RectangleShape hpBar;
	sf::CircleShape pos1;
	sf::CircleShape pos2;
	sf::CircleShape pos3;
	sf::Vector2f Pos;
	float Speed = 0;
	float ySpeed = 0;

	bool isAttack = false;
	int xDir;

public:
	BossMonster(const std::string& textureId, const std::string& n);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetPlayer(Player* player);
	void OnHit(float dt);
	void TurnToPlayer();
	void Attack1(float dt);
};

