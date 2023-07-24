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

	sf::Vector2f sPos;
	sf::Vector2f ePos;

	bool Start = false;
	float Speed = 0;
	float ySpeed = 0;
	int posNum;
	int currPosNum;

	bool Left;
	bool selectPos;
	bool isAttack = false;
	bool parabola = false;
	bool die = false;
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
	void Attack1(float dt, sf::Vector2f pos);
	void Attack2(float dt);
	void Attack3(float dt, sf::Vector2f pos);

	float calculateParabolaY(float x, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float jumpHeight) {
		float a = jumpHeight / ((endPoint.x - startPoint.x / 2) * (endPoint.x - startPoint.x / 2));
		float b = -2.0f * a * (endPoint.x - startPoint.x / 2);
		float c = startPoint.y;
		return a * x * x + b * x + c;
	}
};

