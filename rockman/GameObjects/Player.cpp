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
#include "OnGroundState.h"
#include "JumpingState.h"

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
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Dash.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Saber.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Drag.csv"));

	animation.SetTarget(&sprite);
	sprite.setScale(3, 3);
	
	SetOrigin(Origins::BC);
}

void Player::Release()
{
	SpriteGo::Release();

}

void Player::Reset()
{
	SpriteGo::Reset();
	
	sprite.setScale(3, 3);
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	SetOrigin(origin);
	animation.Update(dt);
	currentClip = animation.GetCurClip();

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
	
	std::cout << onGround << std::endl;
	SetPosition(position.x, position.y - direction.y * ySpeed * dt);

	//// 이동
	direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);

	if (!isDash)
		SetPosition(position + direction * speed * dt);
	if (isDash)
		SetPosition(position + sprite.getScale() * 200.f * dt);

	SetPosition(position.x, position.y - ySpeed * dt);

	ySpeed -= gravity * dt;
	if (ySpeed <= -800) ySpeed = -800;
	
	
	
	currentState->Checking();
	currentState->Idle(dt);
	currentState->Falling();

	//좌우 이동
	if (INPUT_MGR.GetKey(sf::Keyboard::Left) || 
		INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		currentState->Moving(dt);
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Z))
	{
		currentState->Dash(dt);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Z))
	{
		currentState->Dashing();
	}
	if (INPUT_MGR.GetKeyUp(sf::Keyboard::Z))
	{
		currentState->DashEnd(dt);
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::X))
	{
		currentState->Jump(dt);
	}
	if (INPUT_MGR.GetKeyUp(sf::Keyboard::X))	
	{
		currentState->JumpEnd(dt);
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::C))
	{
		currentState->Saber(dt);
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

void Player::InputKey()
{
}

void Player::OnHitted(int damage)
{
}

void Player::OnDie()
{
}

void Player::OnGround()
{
	if (onGround)
		return;
	ySpeed = 20.f;
	currentState->Landing();
	onGround = true;
}

void Player::Drag(float dt)
{
	currentState->WallDrag(dt);
}

void Player::ChangeGround()
{
	currentState = onGroundState;
	currentState->SetPlayer(this);
}

void Player::ChangeJump()
{
	onGround = false;
	currentState = jumpingState;
	currentState->SetPlayer(this);
}