#pragma once
#include "Scene.h"
#include "ObjectPool.h"

class Player;	

class Stage1_1 : public Scene
{
protected:
    Player* player;
    sf::Vector2f windowSize;
    sf::Vector2f centerPos;
    sf::RectangleShape rect;


public:
	Stage1_1();
	virtual ~Stage1_1() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

