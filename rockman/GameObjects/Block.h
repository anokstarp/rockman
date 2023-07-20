#pragma once
#include "GameObject.h"
#include "AnimationController.h"
enum class BlockType
{
	None,
	Block = 1,
	Door,
};

class Block : public GameObject
{
protected:
	sf::RectangleShape block;
	sf::Sprite sprite;
	BlockType type = BlockType::Block;

	AnimationController animation;
public:
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
	void SetBlockType(BlockType type);

	sf::FloatRect GetGlobalBounds();
	Collision CheckCollision(sf::FloatRect ballRect);
	Collision CheckCollisionState_1(sf::FloatRect ballRect);
};