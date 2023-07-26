#include "stdafx.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"
#include "ResourceMgr.h"
#include "Scene.h"
#include "Stage1_1.h"
#include "SceneMgr.h"

Bullet::Bullet(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{
}

Bullet::~Bullet()
{
}

void Bullet::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed)
{
	animation.Play("Bullet");
	SetPosition(pos);

	direction = dir;
	this->speed = speed;
	type = Type::bullet;
}

void Bullet::BossFire(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed)
{
	animation.Play("Fire");
	SetPosition(pos);

	direction = dir;
	this->speed = speed;
	type = Type::Fire;
}

void Bullet::Throw(const sf::Vector2f& startPos, const sf::Vector2f& highPos, const sf::Vector2f& endPos, float time)
{
	this->startPos = startPos;
	this->highPos = highPos;
	this->endPos = endPos;
	this->time = time;

	animation.Play("Grenade");
	SetPosition(startPos);
	type = Type::grenade;
}

void Bullet::Throw()
{
	float u = 1.f - time;
	float tt = time * time;
	float uu = u * u;

	sf::Vector2f p = uu * position;
	p += 1.2f * u * time * highPos;
	p += tt * endPos;
}


void Bullet::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/GrenadeManBullet.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/GrenadeManGrenade.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/MagamaDragoonFire.csv"));
	animation.SetTarget(&sprite);

	sprite.setScale(3.0, 3.0);
	SetOrigin(Origins::MC);
	sortLayer = 10;
}

void Bullet::Release()
{
	SpriteGo::Release();
}

void Bullet::Reset()
{
	SpriteGo::Reset();

	sprite.setRotation(0.f);
	SetPosition(0.f, 0.f);
	direction = { 0.f, 0.f };
	speed = 0.f;
	range = 1000.f;
}

void Bullet::Update(float dt)
{
	SpriteGo::Update(dt);
	animation.Update(dt);
	SetOrigin(origin);

	if (type == Type::bullet)
	{
		range -= speed * dt;
		if (range < 0.f)
		{
			SCENE_MGR.GetCurrScene()->RemoveGo(this);
			pool->Return(this);
			return;
		}

		position += direction * speed * dt;
		sprite.setPosition(position);
	}

	if (type == Type::Fire)
	{
		range -= speed * dt;
		if (range < 0.f)
		{
			SCENE_MGR.GetCurrScene()->RemoveGo(this);
			pool->Return(this);
			return;
		}

		position += direction * speed * dt;
		sprite.setPosition(position);
	}
	
	if (type == Type::grenade)
	{
		timeElapsed += dt;
		if (timeElapsed > duration)
			timeElapsed = duration;

		float t = timeElapsed / duration;
		sf::Vector2f currentPosition = calculateBezierPoint(t, startPos, highPos, endPos);
		SetPosition(currentPosition);

		if (timeElapsed == duration)
		{
			Scene* scene = SCENE_MGR.GetCurrScene();
			Stage1_1* stage1_1 = dynamic_cast<Stage1_1*>(scene);

			if (stage1_1 != nullptr)
			{
				stage1_1->Boom(this);//¸÷À¸·Ó ¤¿²ã¾ßµÊ
			}

			SCENE_MGR.GetCurrScene()->RemoveGo(this);
			pool->Return(this);
			return;
		}
	}

	if (player != nullptr)
	{
		if (sprite.getGlobalBounds().intersects(player->GetBounds()))
		{
			player->OnHit(damage);

			if (type != Type::Fire)
			{
				SCENE_MGR.GetCurrScene()->RemoveGo(this);
				pool->Return(this);
			}
		}
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

sf::Vector2f Bullet::calculateBezierPoint(float t, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2)
{
	float u = 1.0f - t;
	float tt = t * t;
	float uu = u * u;

	sf::Vector2f p = uu * p0;
	p += 2.0f * u * t * p1;
	p += tt * p2;

	return p;
}
