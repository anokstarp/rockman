#include "stdafx.h"
#include "NormalMonster.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "Utils.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Stage1_1.h"

NormalMonster::NormalMonster(const std::string& textureId, const std::string& n)
	:Monster(textureId, n)
{

}

void NormalMonster::Init()
{
	Monster::Init();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/GrenadeManIdle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/GrenadeManShot.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("csv/Monster/GrenadeManThrow.csv"));
	
	animation.SetTarget(&sprite);
	
	SetOrigin(Origins::BC);

	clip = animation.GetClipPtr("Shot");
	clip->frames[clip->frames.size() - 1].action = [this]() {
		animation.Play("Idle");
	};

	clip = animation.GetClipPtr("Throw");
	clip->frames[clip->frames.size() - 1].action = [this]() {
		animation.Play("Idle");
	};
	
	healthPoint = 50;
}

void NormalMonster::Release()
{
	Monster::Release();
}

void NormalMonster::Reset()
{
	Monster::Reset();
	animation.Play("Idle");
}

void NormalMonster::Update(float dt)
{
	if (!setting) Setting();

	Monster::Update(dt);
	animation.Update(dt);
	SetOrigin(origin);
	animation.SetSpeed(0.6f);

	if (healthPoint == 0) animation.Stop();

	OnHit(dt);

	clip = animation.GetCurClipPtr();
	
	float distance = abs(player->GetPosition().x - position.x);     

	if (clip->id == "Idle")
	{
		if (distance <= 500.f)
		{
			clip->frames[clip->frames.size() - 1].action = [this]() {
				type = Utils::RandomRange(0, 2);

				TurnToPlayer();
				if (type == 0) animation.Play("Shot");
				if (type == 1) animation.Play("Throw");
			};
			clip->frames[(clip->frames.size() - 1) / 2].action = [this]() {
				type = Utils::RandomRange(0, 2);

				TurnToPlayer();
				if (type == 0) animation.Play("Shot");
				if (type == 1) animation.Play("Throw");
			};
		}
		else
		{
			clip->frames[clip->frames.size() - 1].action = [this]() {
				animation.Play("Idle");
			};
			clip->frames[(clip->frames.size() - 1) / 2].action = [this]() {
				animation.Play("Idle");
			};
		}
	}
}

void NormalMonster::Draw(sf::RenderWindow& window)
{
	Monster::Draw(window);
}

void NormalMonster::TurnToPlayer()
{
	if (player->GetPosition().x < position.x)
		sprite.setScale(3.0, 3.0);
	else
		sprite.setScale(-3.0, 3.0);
}

void NormalMonster::CheckIdle()
{
	if (animation.GetCurClip() == "Shot") return;
	if (animation.GetCurClip() == "Throw") return;
	
	animation.Play("Idle");
}

void NormalMonster::OnHit(float dt)
{
	int frame = player->OnAttack();
	if (frame == 1)
	{
		isAttack = false;
	}
	if (isAttack) return;

	if (2 < frame && frame < 10)
		if (sprite.getGlobalBounds().intersects(player->GetSaberBounds()))
		{
			isAttack = true;
			healthPoint -= 20;
			Scene* scene = SCENE_MGR.GetCurrScene();
			Stage1_1* stage1_1 = dynamic_cast<Stage1_1*>(scene);

			if (stage1_1 != nullptr)
			{
				stage1_1->AttackEffect(this);
			}
		}

	if (healthPoint <= 0)
	{
		Scene* scene = SCENE_MGR.GetCurrScene();
		Stage1_1* stage1_1 = dynamic_cast<Stage1_1*>(scene);

		if (stage1_1 != nullptr)
		{
			stage1_1->ObejectDie(this);//¸÷À¸·Ó ¤¿²ã¾ßµÊ
		}
		healthPoint = 0;
		sprite.setColor(sf::Color::Color(255, 0, 0, 200));
	}
}

void NormalMonster::Setting()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	Stage1_1* stage1_1 = dynamic_cast<Stage1_1*>(scene);
	poolBullets = stage1_1->GetBullet();

	poolBullets->OnCreate = [this](Bullet* bullet) {
		bullet->pool = poolBullets;
	};

	clip = animation.GetClipPtr("Shot");
	clip->frames[8].action = [this]() {
		Bullet* bullet = poolBullets->Get();
		float dir = sprite.getScale().x > 0 ? -1: 1;
		bullet->Fire(GetPosition() + sf::Vector2f{ dir * 30 , -130 }, { dir , 0 }, 500.f);

		Scene* scene = SCENE_MGR.GetCurrScene();
		Stage1_1* stage1_1 = dynamic_cast<Stage1_1*>(scene);
		if (stage1_1 != nullptr)
		{
			bullet->SetPlayer(stage1_1->GetPlayer());
			stage1_1->AddGo(bullet);
		}
	};

	clip = animation.GetClipPtr("Throw");
	clip->frames[4].action = [this]() {
		Bullet* bullet = poolBullets->Get();
		float dir = sprite.getScale().x > 0 ? -1 : 1;
		sf::Vector2f pos = GetPosition();
		bullet->Throw(pos + sf::Vector2f{ 0, -sprite.getGlobalBounds().height}, {pos.x + dir * 350.f , pos.y - 300.f}, {pos.x + dir * 500.f, pos.y}, 2.f);

		Scene* scene = SCENE_MGR.GetCurrScene();
		Stage1_1* stage1_1 = dynamic_cast<Stage1_1*>(scene);
		if (stage1_1 != nullptr)
		{
			bullet->SetPlayer(stage1_1->GetPlayer());
			stage1_1->AddGo(bullet);
		}
	};
	setting = true;
}
