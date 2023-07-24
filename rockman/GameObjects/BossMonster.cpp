#include "stdafx.h"
#include "BossMonster.h"
#include "Player.h"
#include "ResourceMgr.h"
#include "Utils.h"
#include "InputMgr.h"

BossMonster::BossMonster(const std::string& textureId, const std::string& n)
	:Monster(textureId, n)
{
}

void BossMonster::Init()
{
	Monster::Init();


	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/MagamaDragoon.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/MagamaDragoonAttack1.csv"));
	animation.SetTarget(&sprite);

	healthPoint = 100;
	hpBar.setFillColor(sf::Color::Red);
	Utils::SetOrigin(hpBar, Origins::ML);
	hpBar.setPosition(15500.f, 400.f);
	hpBar.setSize({ 350.f, 40.f });

	pos1.setFillColor(sf::Color::Blue);
	pos2.setFillColor(sf::Color::Blue);
	pos3.setFillColor(sf::Color::Blue);

	pos1.setRadius(5);
	pos2.setRadius(5);
	pos3.setRadius(5);
	
	pos1.setPosition({ 15350.f, 950.f });
	pos2.setPosition({ 15700.f, 950.f });
	pos3.setPosition({ 16050.f, 950.f });
}

void BossMonster::Release()
{
	Monster::Release();
}

void BossMonster::Reset()
{
	Monster::Reset();
}

void BossMonster::Update(float dt)
{
	Monster::Update(dt);
	SetOrigin(Origins::BC);
	animation.Update(dt);

	//animation.Play("IdleBoss1");
	//animation.Play("BossAttack1");
	Attack1(dt);
	TurnToPlayer();
	OnHit(dt);
	if (graceTime > 0)
		sprite.setColor(sf::Color::Color(200,0 , 0));
	if(graceTime <= 0)
		sprite.setColor(sf::Color::Color(255, 255, 255));

	hpBar.setSize({ 400.f * healthPoint / 100, 40.f });
}

void BossMonster::Draw(sf::RenderWindow& window)
{
	Monster::Draw(window);
	window.draw(hpBar);
	window.draw(pos1);
	window.draw(pos2);
	window.draw(pos3);
}

void BossMonster::SetPlayer(Player* player)
{
	Monster::SetPlayer(player);
}

void BossMonster::OnHit(float dt)
{
	graceTime -= dt;
	if (graceTime > 0) return;
	if (graceTime <= 0) graceTime = 0.f;

	int frame = player->OnAttack();

	if (2 < frame && frame < 10)
		if (sprite.getGlobalBounds().intersects(player->GetSaberBounds()))
		{
			healthPoint -= 5;
			graceTime = 2.0f;
		}

	if (healthPoint <= 0)
	{
		healthPoint = 0;
		//»ç¸Á
	}
}

void BossMonster::TurnToPlayer()
{
	if (player->GetPosition().x < position.x)
		sprite.setScale(3.0, 3.0);
	else
		sprite.setScale(-3.0, 3.0);
}

void BossMonster::Attack1(float dt)
{
	delay -= dt;
	if (delay < 0) delay = 0;
	if (delay > 0) return;

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::S))
	{
		if (!isAttack)
		{
			Speed = 600.f;
			ySpeed = 650.f;
			isAttack = true;

			if (sprite.getScale().x > 0)
				xDir = -1;
			else
				xDir = 1;
		}
	}

	Speed -= 700.f * dt;
	ySpeed -= 1200.f * dt;

	if (Speed < 0)
		Speed = 0;
	if (position.y > 950.f)
	{
		SetPosition(position.x, 950.f);
		ySpeed = 0;
		isAttack = false;

		delay = 2.0f;
		animation.Play("IdleBoss1");
	}


	if (isAttack)
	{
		if(animation.GetCurClip() != "BossAttack1")
			animation.Play("BossAttack1");

		SetPosition(position.x + xDir * Speed * dt, position.y - ySpeed * dt);
	}

	/*
	delay -= dt;
	if (dt < 0)
	{
		isAttack = true;
		int pos = Utils::RandomRange(0, 3);

		if (pos == 0)
			Pos = pos1.getPosition();
		else if (pos == 1)
			Pos = pos2.getPosition();
		else if (pos == 2)
			Pos = pos3.getPosition();

		if (sprite.getScale().x > 0)
		{
			xDir = -1;
		}
		else
		{
			xDir = 1;
		}
	}
	*/
}
