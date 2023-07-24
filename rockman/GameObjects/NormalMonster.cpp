#include "stdafx.h"
#include "NormalMonster.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "Utils.h"

NormalMonster::NormalMonster(const std::string& textureId, const std::string& n)
	:Monster(textureId, n)
{
}

void NormalMonster::Init()
{
	Monster::Init();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/GrenadeManIdle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/GrenadeManShot.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/GrenadeManThrow.csv"));
	
	animation.SetTarget(&sprite);
	
	SetOrigin(Origins::BC);
}

void NormalMonster::Release()
{
	Monster::Release();
}

void NormalMonster::Reset()
{
	Monster::Reset();
}

void NormalMonster::Update(float dt)
{
	Monster::Update(dt);
	animation.Update(dt);
	SetOrigin(origin);
	animation.SetSpeed(0.4f);

	if (delay > 0)
	{
		delay -= dt;
		isAttack = false;
	}
	if (delay <= 0)
	{
		delay = 0;
		isAttack = true;
	}

	if (!animation.IsPlaying() && !isAttack)
		animation.Play("Idle");


	float distance = abs(player->GetPosition().x - position.x);            

	if (distance <= 330.f)
	{
		std::cout << animation.GetCurClip() << std::endl;
		if (!isAttack)
		{
			TurnToPlayer();
			type = Utils::RandomRange(0, 3);
			isAttack = true;
		}

		if (type == 0)
		{
			if (animation.GetCurClip() != "Shot")
			{
				animation.Play("Shot");
			}
			if (animation.IsEnd())
			{
				isAttack = false;
				delay = 5.0f;
			}
		}
		else if (type == 1)
		{
			if (animation.GetCurClip() != "Throw")
			{
				animation.Play("Throw");
			}
			if (animation.IsEnd())
			{
				isAttack = false;
				delay = 5.0f;
			}
		}
		else if (type == 2)
		{
			isAttack = false;
		}
	}
}

void NormalMonster::Draw(sf::RenderWindow& window)
{
	Monster::Draw(window);
}

void NormalMonster::TurnToPlayer()
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
