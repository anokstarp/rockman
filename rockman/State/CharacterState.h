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

	virtual void Loading(float dt)
	{
		player->SetPosition(player->position + sf::Vector2f(0.f, 1.f) * player->speed * dt * 2.f);
		player->animation.Play("Loading");
		if (player->position.y >= FRAMEWORK.GetWindowSize().y - 150) player->LOADING = true;
	}
	virtual void Load(float dt)
	{
		player->animation.Play("Load");
		player->LOAD = true;
	}
	virtual void Idle(float dt)
	{
	}
	virtual void Move(float dt) = 0;
	virtual void Jump(float dt) = 0;
	virtual void Falling() = 0;
	virtual void Landing() = 0;
};


//
class JumpingState : public CharacterState
{
public:
	virtual void Loading(float dt) override {}
	virtual void Load(float dt) override {}
	virtual void Idle(float dt) override {}
	virtual void Move(float dt) override
	{
		if (player->direction.x < 0)
			player->sprite.setScale(-2, 2);
		else if (player->direction.x > 0)
			player->sprite.setScale(2, 2);
	}
	virtual void Jump(float dt) override {}
	virtual void Falling() override
	{
		if (player->currentClip == "Jump")
		{
			if (player->animation.GetCurFrame() == 11)
				player->animation.SetFrame(9);
		}
		if (player->currentClip != "Jump" && player->ySpeed < 0 )
		{
			if (player->currentClip == "Jump")
			{
				player->animation.Play("Jump");
				player->animation.SetFrame(5);
			}
			if (player->animation.GetCurFrame() == 11)
				player->animation.SetFrame(8);
		}
	}
	virtual void Landing()
	{
		if (player->currentClip == "Jump")
		{
			player->animation.SetFrame(12);
		}
	}
};


//
class OnGroundState : public CharacterState
{
public:
	virtual void Idle(float dt) override
	{
		if (player->currentClip == "Idle") return;
		if (player->currentClip == "Jump") return;
		if (player->direction.x != 0) return;

		player->animation.Play("Idle");
	}
	virtual void Move(float dt) override
	{
		if (player->direction.x < 0)
			player->sprite.setScale(-2, 2);
		else if (player->direction.x > 0)
			player->sprite.setScale(2, 2);

		if (player->currentClip != "Move")
		{
			if (player->direction.x != 0)
			{
				player->animation.Play("Move");
			}
		}
		else if (player->currentClip == "Move")
		{
			if (player->animation.GetCurFrame() == 32)
				player->animation.SetFrame(3);
			if (player->curFrame != player->animation.GetCurFrame())
				std::cout << "Move " << player->animation.GetCurFrame() << std::endl;
			player->curFrame = player->animation.GetCurFrame();
		}
	}
	virtual void Jump(float dt) override
	{
		player->ySpeed = player->jumpForce;
		player->animation.Play("Jump");
		std::cout << "มกวม" << std::endl;
	}
	virtual void Falling() {}
	virtual void Landing() override {}
};