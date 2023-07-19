#include "CharacterState.h"

class JumpingState : public CharacterState
{
public:
	virtual void Checking() override
	{
		if (player->animation.GetCurClip() != "Dash")
			player->isDash = false;

		if (player->animation.GetCurClip() != "Drag") return;

		player->animation.Play("Jump");
		player->animation.SetFrame(6);
	}

	virtual void Moving(float dt) override
	{
		if (player->direction.x < 0)
			player->sprite.setScale(-3, 3);
		else if (player->direction.x > 0)
			player->sprite.setScale(3, 3);
	}
	virtual void JumpEnd(float dt) override
	{
		//키 떼면 바로 떨어지게
		if (player->ySpeed < 0)
			return;

		player->ySpeed = 0;
		player->animation.SetFrame(6);
	}
	virtual void Landing() override
	{
		//착지하면 모션 변경
		if (player->currentClip == "Jump")
		{
			player->animation.SetFrame(12);
			player->ChangeGround();
		}
		if (player->currentClip == "Drag")
		{
			player->ChangeGround();
		}
	}
	virtual void Falling() override
	{
		//계속 떨어지는 모션
		if (player->currentClip == "Jump")
		{
			if (player->animation.GetCurFrame() == 11)
				player->animation.SetFrame(9);
		}
		if (player->currentClip != "Jump" && player->ySpeed < 0)
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
	virtual void Dashing() override
	{
		player->speed = 600.f;
	}

	virtual void WallDrag() override
	{
		if (player->direction.x < 0)
			player->sprite.setScale(-3, 3);
		else if (player->direction.x > 0)
			player->sprite.setScale(3, 3);

		if (player->currentClip == "Drag") return;
			player->animation.Play("Drag");


		if (player->animation.GetCurFrame() == 3)
			player->animation.SetFrame(1);
	}
};