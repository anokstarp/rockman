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
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/MagamaDragoonAttack2.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/MagamaDragoonAttack3.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/MagamaDragoonAttack4.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/MagamaDragoonDie.csv"));
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

	selectPos = true;
	currPosNum = 2;

	animation.Play("IdleBoss1");

	sprite.setScale(3.0f, 3.0f);
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

	if (die) return;

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::S))
	{
		Start = true;
	}

	if (!Start) return;

	//animation.Play("IdleBoss1");
	//animation.Play("BossAttack1");
	OnHit(dt);

	if(healthPoint <= 0)
	{
		animation.Play("BossDie");
		die = true;
	}

	if (graceTime > 0)
		sprite.setColor(sf::Color::Color(200, 0, 0));
	if (graceTime <= 0)
		sprite.setColor(sf::Color::Color(255, 255, 255));

	hpBar.setSize({ 400.f * healthPoint / 100, 40.f });
	if(isAttack == false) delay -= dt;
	if (delay <= 0)
	{
		delay = 0.f;
		isAttack = true;
	}

	if (selectPos)
	{
		do {
			posNum = Utils::RandomRange(0, 3);
			std::cout << "»Ì±â";
		} while (abs(posNum - currPosNum) == 2);

		Left = currPosNum > posNum;
		selectPos = false;
		xDir = sprite.getScale().x > 0 ? 1.f : -1.f;

		if (player->GetPosition().x < pos2.getPosition().x && posNum == 2) 
			parabola = true;
		else if (player->GetPosition().x > pos2.getPosition().x&& posNum == 0)
			parabola = true;
		else 
			parabola = false;
	}

	std::cout << posNum << std::endl;

	if (isAttack)
	{
		if (posNum == currPosNum)
		{
			Attack2(dt);
		}
		else if (posNum == 0)
		{
			if (!parabola)
				Attack1(dt, pos1.getPosition());
			else if (parabola)
			{
				sPos = position;
				Attack3(dt, pos1.getPosition());
			}
		}
		else if (posNum == 1)
		{
			Attack1(dt, pos2.getPosition());
		}
		else if (posNum == 2)
		{
			if (!parabola)
				Attack1(dt, pos3.getPosition());
			else if (parabola)
			{
				sPos = position;
				Attack3(dt, pos3.getPosition());
			}
		}
	}
	

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
			healthPoint -= 20;
			graceTime = 2.0f;
		}

	if (healthPoint <= 0)
	{
		healthPoint = 0;
	}
}

void BossMonster::TurnToPlayer()
{
	if (player->GetPosition().x < position.x)
	{
		sprite.setScale(3.0, 3.0);
	}
	else
	{
		sprite.setScale(-3.0, 3.0);
	}
}

void BossMonster::Attack1(float dt, sf::Vector2f pos)
{
	if (animation.GetCurClip() != "BossAttack1")
		animation.Play("BossAttack1");

	if (animation.GetCurFrame() == 0 && animation.GetCurClip() == "BossAttack1")
	{
		Speed = 800.f;
		ySpeed = 650.f;

		xDir = sprite.getScale().x > 0 ? -3 : 3;
		TurnToPlayer();
	}

			
	Speed -= 700.f * dt;
	ySpeed -= 1200.f * dt;

	SetPosition(position.x + xDir * Speed * dt, position.y - ySpeed * dt);

	if(Speed <= 0) Speed = 0;
	if (Left)
	{
		xDir = -1;
		if (position.x < pos.x)	
		{
			SetPosition(pos.x, position.y);
			Speed = 0.f;
		}
	}
	else
	{
		xDir = 1;
		if (position.x > pos.x)
		{
			SetPosition(pos.x, position.y);	
			Speed = 0.f;
		}
	}

	if (position.y > 950.f)
	{
		SetPosition(position.x, 950.f);
		ySpeed = 0;

		isAttack = false;
		delay = 1.5f;
		currPosNum = posNum;	
		selectPos = true;
		animation.Play("IdleBoss1");
	}
}

void BossMonster::Attack2(float dt)
{
	TurnToPlayer();
	if (animation.GetCurClip() != "BossAttack2")
		animation.Play("BossAttack2");
	
	if(animation.GetCurClip() == "BossAttack2" &&
		animation.GetCurFrame() == 9)
	{
		isAttack = false;
		delay = 1.0f;
		currPosNum = posNum;
		selectPos = true;
		animation.Play("IdleBoss1");
	}
}

void BossMonster::Attack3(float dt, sf::Vector2f pos)
{	

	if (position.y >= 950.f)
	{
		ySpeed = 0.f;
		SetPosition(position.x, pos.y);
	}

	animation.Play("BossAttack3");
	
	SetPosition(position.x + xDir * 300.f * dt, position.y - ySpeed * dt);
	
	if (Left)
	{
		if (position.x < pos.x)
		{
			SetPosition(pos.x, position.y);
			isAttack = false;
			delay = 1.5f;
			currPosNum = posNum;
			selectPos = true;
			animation.Play("IdleBoss1");
		}
	}
	else
	{
		if (position.x > pos.x)
		{
			SetPosition(pos.x, position.y);
			isAttack = false;
			delay = 1.5f;
			currPosNum = posNum;
			selectPos = true;
			animation.Play("IdleBoss1");
		}
	}
}
