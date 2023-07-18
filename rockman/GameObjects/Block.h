#pragma once
#include "GameObject.h"

class Block : public GameObject
{
protected:
	sf::RectangleShape block;

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

	sf::FloatRect GetGlobalBounds();
	int CheckCollision(sf::FloatRect ballRect);
	int CheckCollisionState_1(sf::FloatRect ballRect);
};