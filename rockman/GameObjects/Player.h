#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"

class CharacterState;
class JumpingState;
class OnGroundState;
class WallDragState;
class OnSlopeState;
class VertexArrayGo;
class Block;

class Player : public SpriteGo
{
	friend class CharacterState;
	friend class JumpingState;
	friend class OnGroundState;
	friend class WallDragState;
	friend class OnSlopeState;
	friend class Stage1_1;

protected:
	CharacterState* currentState;

	OnGroundState* onGroundState;
	JumpingState* jumpingState;
	WallDragState* wallDragState;
	OnSlopeState* onSlopeState;

	sf::Vector2f direction;

	AnimationController animation;
	AnimationController attack;

	std::string currentClip;
	VertexArrayGo* center;

	SpriteGo* saber;

	bool LOAD = false;
	bool LOADING = false;

	float speed = 300.f;
	float dashSpd = 600.f;
	float wallJumpSpd = 0.f;

	float ySpeed = 0.f;
	float jumpForce = 800.f;
	float gravity = 1800.f;

	int curFrame = 0;
	bool isAttack = false;
	bool isDash = false;
	bool onGround = true;
	bool onWall = false;
	bool wallJumpRight = false;
	bool wallJumpLeft = false;

	bool left = false;
	bool right = false;
	bool bottom = false;
	bool top = false;

	float intersectX;
	float intersectY;

public:
	Player(const std::string& textureId, const std::string& n);

	void SetState(CharacterState* state);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetWallBounds(const sf::FloatRect& bounds);
	sf::FloatRect GetBounds() { return sprite.getGlobalBounds(); }
	sf::FloatRect GetSaberBounds() { return saber->sprite.getGlobalBounds(); }

	bool isAlive = false;

	void InputKey();

	int OnAttack();
	void OnHitted(int damage);
	void OnDie();

	void OnGround();
	void WallCollision(Block* block);
	void LineCollision(sf::Vector2f pt1, sf::Vector2f pt2);
	bool LineXLine(sf::Vector2f pt1, sf::Vector2f pt2, sf::Vector2f rpt1, sf::Vector2f rpt2);

	bool CharLoad(float dt);
	void ChangeGround();
	void ChangeJump();
	void ChangeWallDrag();
	void ChangeSlope();

	void OnHit(int damage);

	sf::Vector2f GetCharCenter();

};

