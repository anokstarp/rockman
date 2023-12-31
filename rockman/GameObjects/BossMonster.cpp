#include "stdafx.h"
#include "BossMonster.h"
#include "Player.h"
#include "ResourceMgr.h"
#include "Utils.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Stage1_1.h"

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
	hpBar.setPosition(16078.f, 641.f);
	hpBar.setSize({ 19.f, 94.f * player->GetHp() / 100 });
	Utils::SetOrigin(hpBar, Origins::BL);

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
	if(!isSetting) Setting();

	Monster::Update(dt);
	SetOrigin(Origins::BC);
	animation.Update(dt);

	if (die)
	{
		time += dt;
		if (time >= 0.2f)
		{
			time -= 0.2f;
			count++;

			Scene* scene = SCENE_MGR.GetCurrScene();
			Stage1_1* stage1_1 = dynamic_cast<Stage1_1*>(scene);

			if (count > 15)
			{
				stage1_1->ObejectDie(this);
				stage1_1->PlayerRecall(player);
				return;
			}
			if (stage1_1 != nullptr)
			{
				stage1_1->BoomEffect(this);
			}
		}
		return;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::S))
	{
		Start = true;
	}

	if (!Start) return;

	//animation.Play("IdleBoss1");
	//animation.Play("BossAttack1");
	OnHit(dt);
	hpBar.setSize({ 19.f, 94.f * healthPoint / 100 });
	Utils::SetOrigin(hpBar, Origins::BL);

	if(healthPoint <= 0)
	{
		animation.Play("BossDie");
		die = true;
	}

	if (graceTime > 0)
		sprite.setColor(sf::Color::Color(200, 0, 0));
	if (graceTime <= 0)
		sprite.setColor(sf::Color::Color(255, 255, 255));

	

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

			Scene* scene = SCENE_MGR.GetCurrScene();
			Stage1_1* stage1_1 = dynamic_cast<Stage1_1*>(scene);

			if (stage1_1 != nullptr)
			{
				stage1_1->AttackEffect(this);
			}
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
		ySpeed = 600.f;

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
	timeElapsed += dt;
	if (timeElapsed > duration)
		timeElapsed = duration;

	float t = timeElapsed / duration;

	float high = (position.x + pos.x) * 0.5f;
	sf::Vector2f curPos = calculateBezierPoint(t, position, { high, position.y - 600.f }, pos);
	sprite.setPosition(curPos);
	animation.Play("BossAttack3");
	
	if (timeElapsed == duration)
	{
		timeElapsed = 0.f;
		SetPosition(curPos);
		isAttack = false;
		delay = 1.5f;
		currPosNum = posNum;
		selectPos = true;
		animation.Play("IdleBoss1");
	}
}

void BossMonster::Setting()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	Stage1_1* stage1_1 = dynamic_cast<Stage1_1*>(scene);
	poolBullets = stage1_1->GetBullet();

	poolBullets->OnCreate = [this](Bullet* bullet) {
		bullet->pool = poolBullets;
	};

	clip = animation.GetClipPtr("BossAttack2");
	for (int i = 6; i < 10; i++)
	{
		clip->frames[i].action = [this]() {
			Bullet* bullet = poolBullets->Get();
			float dir = sprite.getScale().x > 0 ? -1 : 1;
			bullet->BossFire(GetPosition() + sf::Vector2f{ dir * 30 , -130 }, { dir , 0 }, 1000.f);

			Scene* scene = SCENE_MGR.GetCurrScene();
			Stage1_1* stage1_1 = dynamic_cast<Stage1_1*>(scene);
			if (stage1_1 != nullptr)
			{
				bullet->SetPlayer(stage1_1->GetPlayer());
				stage1_1->AddGo(bullet);
			}
		};
	}

	isSetting = true;
}

sf::Vector2f BossMonster::calculateBezierPoint(float t, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2)
{
	float u = 1.0f - t;
	float tt = t * t;
	float uu = u * u;

	sf::Vector2f p = uu * p0;
	p += 2.0f * u * t * p1;
	p += tt * p2;

	return p;
}
