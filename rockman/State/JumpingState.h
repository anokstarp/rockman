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
		//Ű ���� �ٷ� ��������
		if (player->ySpeed < 0)
			return;

		player->ySpeed = 0;
		player->animation.SetFrame(6);
	}
	virtual void Landing() override
	{
		//�����ϸ� ��� ����
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
		//��� �������� ���
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