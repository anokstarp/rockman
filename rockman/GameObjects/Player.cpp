#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Stage1_1.h"
#include "Utils.h"
#include "ResourceMgr.h"
#include "Framework.h"

Player::Player(const std::string& textureId = "", const std::string& n = "")
	: SpriteGo(textureId, n)
{
}

void Player::Init()
{
	SpriteGo::Init();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Move.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Loading.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Load.csv"));

	animation.SetTarget(&sprite);
	sprite.setScale(2, 2);
	
	SetOrigin(Origins::BC);
}

void Player::Release()
{
	SpriteGo::Release();

}

void Player::Reset()
{
	SpriteGo::Reset();
	
	sprite.setScale(2, 2);
	animation.Play("Loading");
}

void Player::Update(float dt)
{
	SetOrigin(origin);
	animation.Update(dt);
	SpriteGo::Update(dt);
	currentClip = animation.GetCurClip();
	
	std::cout << currentClip << animation.GetCurFrame() << std::endl;

	if (!LOAD)
	{
		SetPosition(position + sf::Vector2f(0.f, 1.f) * speed * dt * 2.f);
		if (position.y >= FRAMEWORK.GetWindowSize().y - 100) LOAD = true;
		return;
	}

	if (!LOADING && currentClip != "Load")
	{
		animation.Play("Load");
		LOADING = true;
		return;
	}
	if (currentClip == "Load" && animation.GetCurFrame() < 17) return;
	
	



	// ÀÌµ¿
	direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	SetPosition(position + direction * speed * dt);

	if (direction.x < 0)
		sprite.setScale(-2, 2);
	else if(direction.x > 0)
		sprite.setScale(2, 2);


	if (currentClip != "Move")
	{
		if (direction.x != 0)
		{
			animation.Play("Move");
		}
	}
	else if (currentClip == "Move")
	{
		if (animation.GetCurFrame() == 32)
			animation.SetFrame(3);
		if(curFrame != animation.GetCurFrame())
			std::cout << "Move " << animation.GetCurFrame() << std::endl;
		curFrame = animation.GetCurFrame();
	}

	if (currentClip != "Idle")
	{
		if (direction.x == 0)
		{
			animation.Play("Idle");
		}
	}

}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::SetWallBounds(const sf::FloatRect& bounds)
{
}

void Player::OnHitted(int damage)
{
}

void Player::OnDie()
{
}
