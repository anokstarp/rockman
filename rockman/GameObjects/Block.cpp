#include "stdafx.h"
#include "Block.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "SpriteGo.h"
#include "Player.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Stage1_1.h"

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
	OnHit();

	if (isBroken && type != BlockType::Broken)
		type = BlockType::Broken;

	OpenCloseDoor(dt);
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

void Block::SetBlockType(BlockType type, Player* player)
{
	this->type = type;
	if (type == BlockType::Breakable || type == BlockType::UnClimbable)
	{
		this->player = player;
	}
}

void Block::OnHit()
{
	if (type != BlockType::Breakable && type != BlockType::UnClimbable) return;
	if (isBroken) return;

	int frame = player->OnAttack();
	if (frame == 1)
	{
		isAttacked = false;
	}

	if (isAttacked) return;

	if (2 < frame && frame < 10)
		if (block.getGlobalBounds().intersects(player->GetSaberBounds()))
		{
			healthPoint -= 5;
			isAttacked = true;

			Scene* scene = SCENE_MGR.GetCurrScene();
			Stage1_1* stage1_1 = dynamic_cast<Stage1_1*>(scene);

			if (stage1_1 != nullptr)
			{
				stage1_1->BlockAttackEffect(this);
			}
		}

	if (healthPoint <= 0)
		isBroken = true;
}

void Block::OpenCloseDoor(float dt)
{
	if (type != BlockType::Door) return;

	animation.Update(dt);
	sprite->SetOrigin(Origins::MC);
	sprite->SetPosition(position);
	SetOrigin(Origins::MC);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		std::cout << "¹® ¿­¸²";
		doorOpen = true;
		animation.Play("DoorOpen");
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	{
		std::cout << "¹® ´ÝÈû";
		doorOpen = false;
		animation.Play("DoorClose");
	}
	SetSize(sprite->sprite.getGlobalBounds().width, sprite->sprite.getGlobalBounds().height);

}

Collision Block::CheckCollisionState(sf::FloatRect playerRect)
{
	if (type == BlockType::Broken) return Collision::None;

	sf::FloatRect intersect;
	sf::FloatRect blockRect = block.getGlobalBounds();
	float halfWidth = playerRect.width * 0.5f;

	//intersect¿¡ °ãÄ¡´Â ºÎºÐÀÇ rect°¡ µé¾î¿Â´Ù
	if (blockRect.intersects(playerRect, intersect))
	{
		if (intersect.width < intersect.height) //³ôÀÌ°¡ ³ÐÀÌº¸´Ù Å¬ ¶§ == ¿·¿¡¼­ ºÎµúÈû
		{	
			if(intersect.left == playerRect.left) //°ãÄ¡´Â ºÎºÐ ¿ÞÂÊÀÌ ÇÃ·¹ÀÌ¾î ¿ÞÂÊÀÌ¶û °°À¸¸é ¿À¸¥ÂÊ¿¡¼­ ºÎµúÈû
			{
				return Collision::Right;
			}
			else if(intersect.left >= playerRect.left)//¿ÞÂÊ¿¡¼­ ºÎµúÈû
			{
				return Collision::Left;
			}
		}
		else //³ÐÀÌ°¡ ³ôÀÌº¸´Ù Å¬ ¶§ == À§¾Æ·¡¼­ ºÎµúÈû
		{
			if(intersect.top + intersect.height < playerRect.top + playerRect.height) 
				//°ãÄ¡´Â ºÎºÐ ¹Ù´ÚÀÌ ÇÃ·¹ÀÌ¾î ¹Ù´Úº¸´Ù ÀÛÀ¸¸é ¾Æ·¡¿¡¼­ ºÎµúÈû
			{
				return Collision::Bottom;
			}
			else if(intersect.top > playerRect.top)//À§¿¡¼­ ºÎµúÈû
			{
				return Collision::Top;
			}
		}
	}
	return Collision::None;
}