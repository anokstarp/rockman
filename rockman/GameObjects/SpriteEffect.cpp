#include "stdafx.h"
#include "SpriteEffect.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Utils.h"
#include "ResourceMgr.h"

SpriteEffect::SpriteEffect(const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n)
{
}

void SpriteEffect::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Effect/Boom.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Effect/Attack.csv"));
	animation.SetTarget(&sprite);

	sprite.setScale(3.0, 3.0);
}

void SpriteEffect::Reset()
{
	SpriteGo::Reset();
	timer = 0.f;
	//sprite.setColor(sf::Color::Color(255, 255, 255, 255));
}


void SpriteEffect::Update(float dt)
{
	if (!isSetting) Setting();
	SpriteGo::Update(dt);
	animation.Update(dt);
	SetOrigin(Origins::BC);

	if (type == Effect::Boom)
	{
		if (animation.GetCurClip() != "Boom") animation.Play("Boom");
	}
	else if (type == Effect::Attack)
	{
		sprite.setScale(Dir, 3.0);
		if (animation.GetCurClip() != "Attack") animation.Play("Attack");
	}
}

void SpriteEffect::Setting()
{
	clip = animation.GetClipPtr("Boom");
	clip->frames[clip->frames.size() - 1].action = [this]() {
		if (pool != nullptr)
		{
			SCENE_MGR.GetCurrScene()->RemoveGo(this);
			pool->Return(this);
		}
		else
		{
			SetActive(false);
		}
	};

	clip = animation.GetClipPtr("Attack");
	clip->frames[clip->frames.size() - 1].action = [this]() {
		if (pool != nullptr)
		{
			SCENE_MGR.GetCurrScene()->RemoveGo(this);
			pool->Return(this);
		}
		else
		{
			SetActive(false);
		}
	};
	isSetting = true;
}
