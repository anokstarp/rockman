#pragma once
#include "Monster.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "SpriteEffect.h"

class NormalMonster : public Monster
{
protected:
	int type;
	bool isAttack = false;
	float delay = 0.f;
	bool setting = false;

	AnimationClip* clip = nullptr;
	ObjectPool<Bullet>*poolBullets;
	//ObjectPool<SpriteEffect>* poolEffects;

public:
	NormalMonster(const std::string& textureId, const std::string& n);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	
	void TurnToPlayer();
	void CheckIdle();
	void OnHit(float dt);
	void Setting();

};

