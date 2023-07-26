#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"

enum class Type
{
	bullet = 1,
	grenade,
	Fire,
};

class Player;

class Bullet : public SpriteGo
{
protected:
	sf::Vector2f direction;
	float speed = 0.f;
	float range = 2000.f;

	int damage = 10;

	sf::Vector2f startPos;
	sf::Vector2f endPos;
	sf::Vector2f highPos;
	sf::Vector2f p;
	float time;

	float duration = 1.0f;
	float timeElapsed = 0.0f;


	Player* player;
	AnimationController animation;
	Type type;

public:
	ObjectPool<Bullet>* pool;

	Bullet(const std::string& textureId = "", const std::string& n = "");
	virtual ~Bullet() override;

	void SetPlayer(Player* player) { this->player = player; }
	void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed);
	void BossFire(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed);
	void Throw(const sf::Vector2f& startPos, const sf::Vector2f& highPos, const sf::Vector2f& endPos, float speed);
	void Throw();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	sf::Vector2f calculateBezierPoint(float t, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2);
};

