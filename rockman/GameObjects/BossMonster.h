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

	sf::Vector2f startPos;
	sf::Vector2f endPos;
	sf::Vector2f highPos;
	sf::Vector2f p;

	float duration = 1.5f;
	float timeElapsed = 0.0f;

	AnimationClip* clip = nullptr;

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

	sf::Vector2f calculateBezierPoint(float t, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2);
};

