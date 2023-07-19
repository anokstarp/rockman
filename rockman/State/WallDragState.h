#include "CharacterState.h"

class WallDragState : public CharacterState
{
	virtual void Checking()
	{
		if (!player->onWall)
			player->ChangeJump();
	}

	virtual void Jump()
	{
		std::cout << "벽 점프" << std::endl;
		player->wallJumpSpd = 300.f;
		if (player->sprite.getScale().x < 0)
			player->wallJumpRight = true;
		else
			player->wallJumpLeft = true;

		player->animation.Play("WallJump");
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