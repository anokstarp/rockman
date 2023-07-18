#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"

class CharacterState;
class JumpingState;
class OnGroundState;
class Flying;

class Player : public SpriteGo
{
	friend class CharacterState;
	friend class JumpingState;
	friend class OnGroundState;
	friend class Stage1_1;

protected:
	CharacterState* currentState;

	OnGroundState* onGroundState;
	JumpingState* jumpingState;


	sf::Vector2f direction;

	AnimationController animation;
	std::string currentClip;


	bool LOAD = false;
	bool LOADING = false;

	float speed = 300.f;
	float dashSpd = 600.f;

	float ySpeed = 0.f;
	float jumpForce = 800.f;
	float gravity = 1800.f;

	int curFrame = 0;
	bool isDash = false;
	bool onGround = true;

public:
	Player(const std::string& textureId, const std::string& n);

	void SetState(CharacterState* state);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetWallBounds(const sf::FloatRect& bounds);
	sf::FloatRect GetBounds();

	bool isAlive = false;

	void InputKey();

	void OnHitted(int damage);
	void OnDie();

	void OnGround();
	void Drag(float dt);
	void ChangeGround();
	void ChangeJump();
};

