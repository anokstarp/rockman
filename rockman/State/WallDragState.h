#include "CharacterState.h"

class WallDragState : public CharacterState
{
	virtual void Checking()
	{
		player->speed = 300.f;
		if (!player->onWall) player->ChangeJump();
		if (!player->wallJumpLeft) player->ChangeJump();
		if (!player->wallJumpRight) player->ChangeJump();
	}

	virtual void Jump() override
	{
		player->ySpeed = 800;
		player->wallJumpSpd = 400.f;

		if (player->sprite.getScale().x < 0)
			player->wallJumpRight = true;
		else
			player->wallJumpLeft = true;

		player->animation.Play("Jump");
	}
	virtual void Landing() override
	{
		if (player->currentClip == "WallJump") return;
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
};