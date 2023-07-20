#pragma once
#include "Player.h"
#include "Framework.h"

class CharacterState
{
protected:
	Player* player;

public:
	void SetPlayer(Player* player)
	{
		this->player = player;
	}
	virtual void Checking() 
	{
		if (player->animation.GetCurClip() != "Dash")
			player->isDash = false;
	}

	virtual void Loading(float dt)
	{
		player->SetPosition(player->position + sf::Vector2f(0.f, 1.f) * player->speed * dt * 2.f);
		player->animation.Play("Loading");
		if (player->position.y >= FRAMEWORK.GetWindowSize().y - 155) player->LOADING = true;
	}
	virtual void Load(float dt)
	{
		player->animation.Play("Load");
		player->LOAD = true;
	}
	virtual void Idle(float dt) {}
	virtual void Moving(float dt) {}

	virtual void Jump() {}
	virtual void Jumping(float dt) {}
	virtual void JumpEnd(float dt) {}
	virtual void Landing() {}
	virtual void Falling() {}

	virtual void Saber(float dt) {}
	virtual void Fly() {}

	virtual void Dash(float dt) {}
	virtual void Dashing() {}
	virtual void DashEnd(float dt) {}

	virtual void WallDrag() {}
};