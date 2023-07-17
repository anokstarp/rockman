#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Stage1_1.h"
#include "Utils.h"
#include "ResourceMgr.h"
#include "Framework.h"
#include "CharacterState.h"

Player::Player(const std::string& textureId = "", const std::string& n = "")
	: SpriteGo(textureId, n), currentState(nullptr)
{
	onGroundState = new OnGroundState();
	jumpingState = new JumpingState();

	currentState = onGroundState;
	currentState->SetPlayer(this);
}

void Player::Init()
{
	SpriteGo::Init();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Move.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Loading.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Load.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Jump.csv"));

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
}

void Player::Update(float dt)
{
	SetOrigin(origin);
	animation.Update(dt);
	SpriteGo::Update(dt);
	currentClip = animation.GetCurClip();

	std::cout << currentClip;
	std::cout << " " << currentState << std::endl;

	/*if (!LOADING)
	{
		SetPosition(position + sf::Vector2f(0.f, 1.f) * speed * dt * 2.f);
		if (position.y >= FRAMEWORK.GetWindowSize().y - 100) LOADING = true;
		return;
	}

	if (!LOAD && currentClip != "Load")
	{
		animation.Play("Load");
		LOAD = true;
		return;
	}
	if (currentClip == "Load" && animation.GetCurFrame() < 17) return;*/

	if (!LOADING)
	{
		currentState->Loading(dt);
		return;
	}
	if (!LOAD && currentClip != "Load")
	{
		currentState->Load(dt);
		return;
	}
	if (currentClip == "Load" && animation.GetCurFrame() < 17) return;
	
	
	
	SetPosition(position.x, position.y - direction.y * ySpeed * dt);

	// ÀÌµ¿
	direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	SetPosition(position + direction * speed * dt);
	SetPosition(position.x, position.y - ySpeed * dt);
	ySpeed -= gravity * dt;
	if (ySpeed <= -800) ySpeed = -800;

	//currentState->Move(dt);

	/*if (direction.x < 0)
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
		if (curFrame != animation.GetCurFrame())
			std::cout << "Move " << animation.GetCurFrame() << std::endl;
		curFrame = animation.GetCurFrame();
	}*/

	//if (currentClip != "Idle")
	//{
	//	if (direction.x == 0)
	//	{
	//		//animation.Play("Idle");
	//	}
	//}
		
	currentState->Falling();
	currentState->Idle(dt);
	
	if (INPUT_MGR.GetKey(sf::Keyboard::Left) || INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		currentState->Move(dt);
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::X))
	{
		currentState->Jump(dt);
		if (currentState != jumpingState)
		{
			currentState = jumpingState;
			currentState->SetPlayer(this);
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::SetState(CharacterState* state)
{
	if (currentState != nullptr)
	{
		delete currentState;
		currentState = state;
		
	}
	if (currentState == nullptr)
		currentState = state;
}

void Player::SetWallBounds(const sf::FloatRect& bounds)
{
}

sf::FloatRect Player::GetBounds()
{
	return sprite.getGlobalBounds();
}

void Player::OnHitted(int damage)
{
}

void Player::OnDie()
{
}

void Player::OnGround()
{
	ySpeed = 20.f;
	currentState->Landing();

	currentState = onGroundState;
	currentState->SetPlayer(this);
}