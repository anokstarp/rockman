#include "stdafx.h"
#include "Monster.h"

Monster::Monster(const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n)
{
}

void Monster::Init()
{
	SpriteGo::Init();
}

void Monster::Release()
{
	SpriteGo::Release();
}

void Monster::Reset()
{
	SpriteGo::Reset();
}

void Monster::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Monster::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Monster::SetPlayer(Player* player)
{
	this->player = player;
}
