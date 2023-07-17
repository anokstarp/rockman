#include "stdafx.h"
#include "Block.h"

Block::Block(const std::string n)
	:GameObject(n)
{
	block.setSize({ 45.f, 45.f });
}

Block::~Block()
{
	Release();
}

void Block::SetPosition(const sf::Vector2f& p)
{
	position = p;
	block.setPosition(p);
}

void Block::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	block.setPosition(position);
}

void Block::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(block, origin);
	}
}

void Block::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	block.setOrigin(x, y);
}

void Block::Init()
{
}

void Block::Release()
{
}

void Block::Reset()
{
}

void Block::Update(float dt)
{
}

void Block::Draw(sf::RenderWindow& window)
{
	window.draw(block);
}

void Block::SetSize(sf::Vector2f size)
{
	block.setSize(size);
}

void Block::SetSize(float xSize, float ySize)
{
	block.setSize({ xSize, ySize });
}

void Block::SetFillColor(sf::Color color)
{
	block.setFillColor(color);
}

sf::FloatRect Block::GetGlobalBounds()
{
	return block.getGlobalBounds();
}

int Block::CheckCollision(sf::FloatRect ballRect)
{
	return CheckCollisionState_1(ballRect);
}

int Block::CheckCollisionState_1(sf::FloatRect ballRect)
{
	sf::FloatRect intersect;
	sf::FloatRect blockRect = block.getGlobalBounds();

	float ballVerticalMid = ((ballRect.left * 2) + ballRect.width) * 0.5f;
	float ballHorizontalMid = ((ballRect.top * 2) + ballRect.height) * 0.5f;

	float blockVerticalMid = ((blockRect.left * 2) + blockRect.width) * 0.5f;
	float blockHorizontalMid = ((blockRect.top * 2) + blockRect.height) * 0.5f;


	//intersect¿¡ °ãÄ¡´Â ºÎºÐÀÇ rect°¡ µé¾î¿Â´Ù
	if (blockRect.intersects(ballRect, intersect))
	{
		if (intersect.width < intersect.height) //³ôÀÌ°¡ ³ÐÀÌº¸´Ù Å¬ ¶§ == ¿·¿¡¼­ ºÎµúÈû
		{	
			if(intersect.left == ballRect.left) //°ãÄ¡´Â ºÎºÐ ¿ÞÂÊÀÌ ÇÃ·¹ÀÌ¾î ¿ÞÂÊÀÌ¶û °°À¸¸é ¿À¸¥ÂÊ¿¡¼­ ºÎµúÈû
			{
				block.setFillColor(sf::Color::Red);
				return 1;
			}
			else if(intersect.left >= ballRect.left)//¿ÞÂÊ¿¡¼­ ºÎµúÈû
			{
				block.setFillColor(sf::Color::Green);
				return 2;
			}
		}
		else //³ÐÀÌ°¡ ³ôÀÌº¸´Ù Å¬ ¶§ == À§¾Æ·¡¼­ ºÎµúÈû
		{
			if(intersect.top == ballRect.top) //°ãÄ¡´Â ºÎºÐÀÌ À§ÂÊÀÌ ÇÃ·¹ÀÌ¾î À§ÂÊÀÌ¶û °°À¸¸é ¾Æ·¡¿¡¼­ ºÎµúÈû
			{
				block.setFillColor(sf::Color::Magenta);
				return 3;
			}
			else if(intersect.top >= ballRect.top)//À§¿¡¼­ ºÎµúÈû
			{
				block.setFillColor(sf::Color::Yellow);
				return 4;
			}
		}
	}
	return 0;
}