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
#include "WallDragState.h"
#include "OnSlopeState.h"
#include "VertexArrayGo.h"

Player::Player(const std::string& textureId = "", const std::string& n = "")
	: SpriteGo(textureId, n), currentState(nullptr)
{
	onGroundState = new OnGroundState();
	jumpingState = new JumpingState();
	wallDragState = new WallDragState();
	onSlopeState = new OnSlopeState();

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
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/WallJump.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Saber.csv"));

	attack.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Saber1.csv"));

	saber = new SpriteGo("", "Saber");
	saber->sprite.setScale(sprite.getScale());

	animation.SetTarget(&sprite);
	attack.SetTarget(&saber->sprite);

	sprite.setScale(3, 3);
	
	center = new VertexArrayGo("", "PlayerCenter");
	center->vertexArray.resize(2);
	center->vertexArray.setPrimitiveType(sf::Lines);
	
	

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
	attack.Update(dt);


	currentClip = animation.GetCurClip();

	if (CharLoad(dt)) return;

	std::cout << currentState << std::endl;
	//SetPosition(position.x, position.y - direction.y * ySpeed * dt);

	//// �̵�
	direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);

	

	if (wallJumpRight)
	{
		if (!isDash)
			SetPosition(position.x + wallJumpSpd * dt, position.y - ySpeed * dt);
		if (isDash)
			SetPosition(position.x + wallJumpSpd * 2 * dt, position.y - ySpeed * dt);
	}
	else if (wallJumpLeft)
	{
		if(!isDash)
			SetPosition(position.x - wallJumpSpd * dt, position.y - ySpeed * dt);
		if (isDash)
			SetPosition(position.x - wallJumpSpd * 2 * dt, position.y - ySpeed * dt);
	}
	else
	{
		if (!isDash)
			SetPosition(position + direction * speed * dt);
		if (isDash)
			SetPosition(position + sprite.getScale() * 200.f * dt);
		SetPosition(position.x, position.y - ySpeed * dt);
	}
	wallJumpSpd -= gravity * dt;
	if (wallJumpSpd <= 0)
	{
		wallJumpSpd = 0;
		wallJumpRight = false;
		wallJumpLeft = false;
	}

	ySpeed -= gravity * dt;
	if (ySpeed <= -800) ySpeed = -800;
	
	currentState->Checking();
	currentState->Idle(dt);
	currentState->Falling();


	//�¿� �̵�
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

	if (animation.GetCurClip() == "Saber")
	{
		attack.Play("Saber1");
		attack.SetFrame(animation.GetCurFrame());
	}
	

	if (sprite.getScale().x > 0)
		saber->SetPosition(position.x + 110, position.y - 5);
	else
		saber->SetPosition(position.x - 110, position.y - 5);

	saber->SetOrigin(Origins::BC);
	saber->sprite.setScale(-sprite.getScale().x, sprite.getScale().y);
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(center->vertexArray);
	window.draw(saber->sprite);
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
	ySpeed = 20.f;
	currentState->Landing();
	onGround = true;
}

void Player::WallCollision(sf::FloatRect wallBound)
{
	sf::FloatRect intersect;
	sf::FloatRect player = this->sprite.getGlobalBounds();
	float halfWidth = player.width * 0.5f;

	//intersect�� ��ġ�� �κ��� rect�� ���´�
	if (player.intersects(wallBound, intersect))
	{
		onWall = true;
		if (intersect.width < intersect.height) //���̰� ���̺��� Ŭ �� == ������ �ε���
		{
			if (intersect.left == wallBound.left) //��ġ�� �κ� ������ �÷��̾� �����̶� ������ ���ʿ��� �ε���
			{
				SetPosition(wallBound.left - halfWidth, position.y);
				if (onGround) return;
				if (INPUT_MGR.GetKey(sf::Keyboard::Right))
				{
					ySpeed = -40;
					currentState->WallDrag();
					ChangeWallDrag();
				}
				if (INPUT_MGR.GetKeyUp(sf::Keyboard::Right))
				{
					ChangeJump();
				}
			}
			else if (intersect.left >= wallBound.left)//�����ʿ��� �ε���
			{
				SetPosition(wallBound.left + wallBound.width + halfWidth, position.y);
				if (onGround) return;
				if (INPUT_MGR.GetKey(sf::Keyboard::Left))
				{
					ySpeed = -40;
					currentState->WallDrag();
					ChangeWallDrag();
				}
				if (INPUT_MGR.GetKeyUp(sf::Keyboard::Left))
				{
					ChangeJump();
				}
			}
		}
		else //���̰� ���̺��� Ŭ �� == ���Ʒ��� �ε���
		{
			if (intersect.top + intersect.height < wallBound.top + wallBound.height)
				//��ġ�� �κ� �ٴ��� �÷��̾� �ٴں��� ������ ������ �ε���
			{
				ySpeed = -100;
				SetPosition(position.x, wallBound.top);
				OnGround();
			}
			else if (intersect.top > wallBound.top)//�Ʒ����� �ε���
			{
				SetPosition(position.x, wallBound.top + wallBound.height + player.height);
			}
		}
		return;
	}
	onWall = false;
}

void Player::LineCollision(sf::Vector2f pt1, sf::Vector2f pt2)
{
	sf::FloatRect player = sprite.getGlobalBounds();
	float rx = (player.left + player.left + player.width) * 0.5f;
	float ry = player.top;
	float rw = player.width;
	float rh = player.height;

	
	center->vertexArray[0].position = { rx, ry };
	center->vertexArray[1].position = { rx, ry + rh };
	center->vertexArray[0].color = sf::Color::Red;
	center->vertexArray[1].color = sf::Color::Red;

	bool mid = LineXLine(pt1, pt2, center->vertexArray[0].position, center->vertexArray[1].position);

	//right = LineXLine(pt1, pt2, { rx + rw,ry }, { rx + rw,ry + rh });
	//top = LineXLine(pt1, pt2, { rx,ry }, { rx + rw,ry});
	//left = LineXLine(pt1, pt2, { rx, ry }, { rx,ry + rh });
	//bottom = LineXLine(pt1, pt2, { rx,ry + rh }, { rx + rw,ry + rh });

	if (mid) {
		//���ο� �ö�
		ChangeSlope();
		SetPosition(intersectX, intersectY);
	}
	
}

bool Player::LineXLine(sf::Vector2f pt1, sf::Vector2f pt2, sf::Vector2f pt3, sf::Vector2f pt4)
{
	float uA = ((pt4.x - pt3.x) * (pt1.y - pt3.y) - (pt4.y - pt3.y) * (pt1.x - pt3.x))
		/ ((pt4.y - pt3.y) * (pt2.x - pt1.x) - (pt4.x - pt3.x) * (pt2.y - pt1.y));

	float uB = ((pt2.x - pt1.x) * (pt1.y - pt3.y) - (pt2.y - pt1.y) * (pt1.x - pt3.x)) 
		/ ((pt4.y - pt3.y) * (pt2.x - pt1.x) - (pt4.x - pt3.x) * (pt2.y - pt1.y));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
		intersectX = pt1.x + (uA * (pt2.x - pt1.x));
		intersectY = pt1.y + (uA * (pt2.y - pt1.y));
		return true;
	}
	return false;
}

void Player::ChangeGround()
{
	currentState = onGroundState;
	currentState->SetPlayer(this);
}

bool Player::CharLoad(float dt)
{
	if (!LOADING)
	{
		currentState->Loading(dt);
		return true;
	}
	if (!LOAD && currentClip != "Load")
	{
		currentState->Load(dt);
		return true;
	}
	if (currentClip == "Load" && animation.GetCurFrame() < 17) return true;
	return false;
}

void Player::ChangeJump()
{
	onGround = false;
	currentState = jumpingState;
	currentState->SetPlayer(this);
}

void Player::ChangeWallDrag()
{
	currentState = wallDragState;
	currentState->SetPlayer(this);
}

void Player::ChangeSlope()
{
	currentState = onSlopeState;
	currentState->SetPlayer(this);
}
