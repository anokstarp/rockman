#include "stdafx.h"
#include "Block.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "SpriteGo.h"

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
	block.setOutlineThickness(3);
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/DoorOpen.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/DoorClose.csv"));

	sprite = new SpriteGo("", "Door");
	sprite->sprite.setScale(3.0, 3.0);
	animation.SetTarget(&sprite->sprite);
	animation.Play("DoorClose");
}

void Block::Release()
{
}

void Block::Reset()
{
}

void Block::Update(float dt)
{
	if (type == BlockType::Door)
	{
		animation.Update(dt);
		sprite->SetOrigin(Origins::MC);
		sprite->SetPosition(position);
		SetOrigin(Origins::MC);
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		{
			std::cout << "�� ����";
			animation.Play("DoorOpen");
		}
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		{
			std::cout << "�� ����";
			animation.Play("DoorClose");
		}
		SetSize(sprite->sprite.getGlobalBounds().width, sprite->sprite.getGlobalBounds().height);
	}
}

void Block::Draw(sf::RenderWindow& window)
{
	window.draw(block);
	window.draw(sprite->sprite);
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

void Block::SetOutlineColor(sf::Color color)
{
	block.setOutlineColor(color);
}

void Block::SetBlockType(BlockType type)
{
	this->type = type;
}

sf::FloatRect Block::GetGlobalBounds()
{
	return block.getGlobalBounds();
}

Collision Block::CheckCollision(sf::FloatRect ballRect)
{
	return CheckCollisionState_1(ballRect);
}

Collision Block::CheckCollisionState_1(sf::FloatRect ballRect)
{
	sf::FloatRect intersect;
	sf::FloatRect blockRect = block.getGlobalBounds();

	float ballVerticalMid = ((ballRect.left * 2) + ballRect.width) * 0.5f;
	float ballHorizontalMid = ((ballRect.top * 2) + ballRect.height) * 0.5f;

	float blockVerticalMid = ((blockRect.left * 2) + blockRect.width) * 0.5f;
	float blockHorizontalMid = ((blockRect.top * 2) + blockRect.height) * 0.5f;


	//intersect�� ��ġ�� �κ��� rect�� ���´�
	if (blockRect.intersects(ballRect, intersect))
	{
		if (intersect.width < intersect.height) //���̰� ���̺��� Ŭ �� == ������ �ε���
		{	
			if(intersect.left == ballRect.left) //��ġ�� �κ� ������ �÷��̾� �����̶� ������ �����ʿ��� �ε���
			{
				//block.setFillColor(sf::Color::Red);
				return Collision::Right;
			}
			else if(intersect.left >= ballRect.left)//���ʿ��� �ε���
			{
				//block.setFillColor(sf::Color::Green);
				return Collision::Left;
			}
		}
		else //���̰� ���̺��� Ŭ �� == ���Ʒ��� �ε���
		{
			if(intersect.top + intersect.height < ballRect.top + ballRect.height) 
				//��ġ�� �κ� �ٴ��� �÷��̾� �ٴں��� ������ �Ʒ����� �ε���
			{
				//block.setFillColor(sf::Color::Magenta);
				return Collision::Bottom;
			}
			else if(intersect.top > ballRect.top)//������ �ε���
			{
				//block.setFillColor(sf::Color::Yellow);
				return Collision::Top;
			}
		}
	}
	return Collision::None;
}