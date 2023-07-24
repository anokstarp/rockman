#pragma once
#include "Scene.h"
#include "ObjectPool.h"

class Player;
class BossMonster;

class Stage1_1 : public Scene
{
protected:
    Player* player;
	BossMonster* boss;

    sf::Vector2f windowSize;
    sf::Vector2f centerPos;
    sf::RectangleShape rect;
	sf::VertexArray array;

	bool wallJumpLeft = false;
	bool wallJumpRight = false;


public:
	Stage1_1();
	virtual ~Stage1_1() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void CheckBlockCollision(float dt);
	void CheckLineCollision();

	sf::Vector2f CameraPosition();

	void ManageWall();
};

