#pragma once
#include "GameObject.h"
#include "AnimationController.h"

class SpriteGo;
class Player;

class Block : public GameObject
{
protected:
	sf::RectangleShape block;
	SpriteGo* sprite;
	
	BlockType type = BlockType::Block;
	int healthPoint = 10;

	AnimationController animation;
	Player* player = nullptr;

public:
	bool doorOpen = false;
	bool isBroken = false;
	bool isAttacked = false;

	Block(const std::string n = "");
	virtual ~Block();

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetSize(sf::Vector2f size);
	void SetSize(float xSize, float ySize);
	void SetFillColor(sf::Color color);
	void SetOutlineColor(sf::Color color);
	void SetBlockType(BlockType type, Player* player = nullptr);

	void OnHit();
	void OpenCloseDoor(float dt);

	sf::FloatRect GetGlobalBounds() { return block.getGlobalBounds(); }
	Collision CheckCollisionState(sf::FloatRect ballRect);
	BlockType GetBlockType() { return type; }
};