#include "stdafx.h"
#include "Stage1_1.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "VertexArrayGo.h"
#include "Framework.h"

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
	
}

void Stage1_1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	//drawGrid(window, 20, 20);
}
