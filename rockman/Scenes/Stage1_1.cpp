#include "stdafx.h"
#include "Stage1_1.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "VertexArrayGo.h"
#include "Framework.h"
#include "Block.h"

Stage1_1::Stage1_1()
	: Scene(SceneId::Stage1_1)
{
}

Stage1_1::~Stage1_1()
{
	Release();
}

void Stage1_1::Init()
{
	Release();
	windowSize = FRAMEWORK.GetWindowSize();
	centerPos = windowSize * 0.5f;

	player = (Player*)AddGo(new Player("", "player"));
	player->SetOrigin(Origins::BC);
	player->SetPosition(centerPos.x, 0);
	player->sortLayer = 1;

	Block* block = (Block*)AddGo(new Block("ABC"));
	block->SetPosition(0, windowSize.y);
	block->SetSize(windowSize.x, 150.f);
	block->SetOrigin(Origins::BL);

	SpriteGo* map = (SpriteGo*)AddGo(new SpriteGo("graphics/map1_1.png", "map"));
	map->SetPosition(0, 0);
	map->sprite.setScale(3, 3);
	map->sortLayer = 0;


	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void Stage1_1::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void Stage1_1::Enter()
{
	Scene::Enter();

	worldView.setSize(windowSize);
	worldView.setCenter(centerPos);
	uiView.setSize(windowSize);

}

void Stage1_1::Exit()
{
	Scene::Exit();
}

void Stage1_1::Update(float dt)
{
	Scene::Update(dt);
	//worldView.setCenter(player->GetPosition().x, centerPos.y);
	worldView.setCenter(player->GetPosition());

	Block* block = (Block*)FindGo("ABC");
	int Collide = block->CheckCollision(player->GetBounds());
	sf::FloatRect blockRect = block->GetGlobalBounds();
	
	switch (Collide)
	{
	case 1: //오른쪽
		player->SetPosition(blockRect.left + blockRect.width, player->GetPosition().y);
		break;
	case 2: //왼쪽
		player->SetPosition(blockRect.left, player->GetPosition().y);
		break;
	case 3: //아래
		player->SetPosition(player->GetPosition().x, blockRect.top + blockRect.height);
		break;
	case 4: //위에
		player->SetPosition(player->GetPosition().x, blockRect.top);
		player->OnGround();
		//isJump = false;
		break;
	}
}

void Stage1_1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	//drawGrid(window, 20, 20);
}
