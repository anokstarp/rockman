#include "CharacterState.h"

class OnSlopeState : public CharacterState
{
public:
	virtual void Checking() override
	{
		//player->ySpeed = -40;
		player->speed = 300.f;
		if (player->currentClip != "Dash")
		{
			player->isDash = false;
		}
		/*if (player->ySpeed <= -50)
		{
			player->onGround = false;
			player->animation.Play("Jump");
			player->animation.SetFrame(6);
			player->ChangeJump();
		}*/
	}

	virtual void Idle(float dt) override
	{
		//Idle 모션
		if (player->currentClip == "Idle") return;
		if (player->currentClip == "Jump") return;
		if (player->currentClip == "Dash")
			if (player->animation.GetCurFrame() <= 9) return;

		if (player->currentClip == "Saber")
			if (player->animation.GetCurFrame() <= 14) return;
		if (player->direction.x != 0) return;

		player->animation.Play("Idle");
	}
	virtual void Moving(float dt)
	{
		if (player->ySpeed <= -200)
			player->ySpeed = -200;

		if (player->currentClip == "Dash")
			if (player->animation.GetCurFrame() <= 9) return;

		if (player->direction.x < 0)
			player->sprite.setScale(-3, 3);
		else if (player->direction.x > 0)
			player->sprite.setScale(3, 3);

		if (player->currentClip != "Move")
			player->animation.Play("Move");

		if (player->currentClip == "Move")
		{
			if (player->animation.GetCurFrame() == 32)
				player->animation.SetFrame(3);
		}
	}
	virtual void Jump() override
	{
		//점프
		player->SetPosition(player->GetPosition().x, player->GetPosition().y - 35.f);
		player->ySpeed = player->jumpForce;
		player->animation.Play("Jump");
		player->ChangeJump();; //상태 변경
	}
	virtual void Saber(float dt)
	{
		if (player->currentClip != "Saber")
		{
			player->animation.Play("Saber");
		}
	}

	virtual void Dash(float dt)
	{
		player->animation.Play("Dash");
	}
	virtual void Dashing()
	{
		if (player->currentClip != "Dash")
		{
			player->isDash = false;
			return;
		}

		if (player->animation.GetCurFrame() == 6)
			player->animation.SetFrame(4);

		if (player->animation.GetCurFrame() > 2)
			player->isDash = true;
	}
	virtual void DashEnd(float dt)
	{
		if (player->currentClip == "Dash")
		{
			player->animation.SetFrame(6);
		}
	}
};