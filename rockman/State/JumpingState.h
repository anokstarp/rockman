#include "CharacterState.h"

class JumpingState : public CharacterState
{
public:
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

	virtual void WallDrag(float dt) override
	{
		if (player->direction.x < 0)
			player->sprite.setScale(-3, 3);
		else if (player->direction.x > 0)
			player->sprite.setScale(3, 3);

		player->animation.Play("Drag");
	}
};