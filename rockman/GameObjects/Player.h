#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction;

	AnimationController animation;
	std::string currentClip;

	bool LOAD = false;
	bool LOADING = false;

	float speed = 300.f;
	int curFrame = 0;

public:
	Player(const std::string& textureId, const std::string& n);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetWallBounds(const sf::FloatRect& bounds);

	bool isAlive = false;

	void OnHitted(int damage);
	void OnDie();
};

