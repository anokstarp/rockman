#pragma once
#include "Scene.h"
#include "ObjectPool.h"

class Player;
class BossMonster;
class NormalMonster;
class Bullet;
class SpriteEffect;
class Monster;
class Block;
class RectGo;

class Stage1_1 : public Scene
{
protected:
    Player* player;
	RectGo* hpBar;

	BossMonster* boss;
	NormalMonster* monster[10];

    sf::Vector2f windowSize;
    sf::Vector2f centerPos;
    sf::RectangleShape rect;
	sf::VertexArray array;

	bool wallJumpLeft = false;
	bool wallJumpRight = false;

	ObjectPool<Bullet> poolBullets;
	ObjectPool<SpriteEffect> effectPool;

public:
	Stage1_1();
	virtual ~Stage1_1() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void CheckBlockCollision(float dt);
	void CheckLineCollision();
	Player* GetPlayer() { return player; }

	sf::Vector2f CameraPosition();

	void ManageWall();

	ObjectPool<Bullet>* GetBullet() { return &poolBullets; }
	void ObejectDie(Monster* monster);
	void BoomEffect(Monster* monster);
	void Boom(Bullet* bullet);
	void AttackEffect(Monster* monster);
	void BlockAttackEffect(Block* block);
	void PlayerRecall(Player* player);
};

