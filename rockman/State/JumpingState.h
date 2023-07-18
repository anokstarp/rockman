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

	virtual void WallDrag(float dt) override
	{
		if (player->direction.x < 0)
			player->sprite.setScale(-3, 3);
		else if (player->direction.x > 0)
			player->sprite.setScale(3, 3);

		player->animation.Play("Drag");
	}
};