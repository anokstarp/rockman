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
	player->SetPosition(10000, 0);
	player->sortLayer = 1;

	Block* block1 = (Block*)AddGo(new Block("Block1"));
	block1->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block1->SetOutlineColor(sf::Color::Red);
	block1->SetPosition(0, windowSize.y);
	block1->SetSize(11400.f, 135.f);
	block1->SetOrigin(Origins::BL);
	block1->sortLayer = 10;

	Block* block2 = (Block*)AddGo(new Block("Block2"));
	block2->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block2->SetOutlineColor(sf::Color::Red);
	block2->SetPosition(12950, 950.f);
	block2->SetSize(4000.f, 150.f);
	block2->SetOrigin(Origins::TL);
	block2->sortLayer = 10;

	Block* block3 = (Block*)AddGo(new Block("Block3"));
	block3->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block3->SetOutlineColor(sf::Color::Red);
	block3->SetPosition(5000, 550.f);
	block3->SetSize(50.f, 200.f);
	block3->SetOrigin(Origins::BL);
	block3->sortLayer = 10;

	Block* block4 = (Block*)AddGo(new Block("Block4"));
	block4->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block4->SetOutlineColor(sf::Color::Red);
	block4->SetPosition(6550, 550.f);
	block4->SetSize(50.f, 200.f);
	block4->SetOrigin(Origins::BL);
	block4->sortLayer = 10;

	Block* block5 = (Block*)AddGo(new Block("Block5"));
	block5->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block5->SetOutlineColor(sf::Color::Red);
	block5->SetPosition(8080, 550.f);
	block5->SetSize(50.f, 200.f);
	block5->SetOrigin(Origins::BL);
	block5->sortLayer = 10;

	//���� ū��
	Block* block6 = (Block*)AddGo(new Block("Block6"));
	block6->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block6->SetOutlineColor(sf::Color::Red);
	block6->SetPosition(9600.f, 550.f);
	block6->SetSize(60.f, 500.f);
	block6->SetOrigin(Origins::BL);
	block6->sortLayer = 10;

	//�� �ܰ� ����
	Block* block7 = (Block*)AddGo(new Block("Block7"));
	block7->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block7->SetOutlineColor(sf::Color::Red);
	block7->SetPosition(0.f, 0.f);
	block7->SetSize(500.f, 700.f);
	block7->SetOrigin(Origins::TR);
	block7->sortLayer = 10;

	//������ ��
	Block* block8 = (Block*)AddGo(new Block("Block8"));
	block8->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block8->SetOutlineColor(sf::Color::Red);
	block8->SetPosition(15140.f, 750.f);
	block8->SetSize(100.f, 400.f);
	block8->SetOrigin(Origins::BL);
	block8->sortLayer = 10;

	SpriteGo* map = (SpriteGo*)AddGo(new SpriteGo("graphics/map1_1.png", "map"));
	map->SetPosition(0, 0);
	map->sprite.setScale(3, 3);
	map->sortLayer = 0;


	VertexArrayGo* square = new VertexArrayGo("", "SlopeLine");
	square->vertexArray.resize(4);
	square->sortLayer = 5;
	square->vertexArray.setPrimitiveType(sf::LinesStrip);
	square->vertexArray[0].position = { 11400, windowSize.y - 140.f };
	square->vertexArray[1].position = { 12950, 950 };
	square->vertexArray[2].position = { 12950, 1050 };
	square->vertexArray[3].position = { 11400, 660 };
	square->vertexArray[0].color = sf::Color::Green;
	square->vertexArray[1].color = sf::Color::Green;
	square->vertexArray[2].color = sf::Color::Red;
	square->vertexArray[3].color = sf::Color::Red;

	VertexArrayGo* cameraLine = new VertexArrayGo("", "SlopeLine");
	cameraLine->vertexArray.resize(6);
	cameraLine->sortLayer = 5;
	cameraLine->vertexArray.setPrimitiveType(sf::Lines);
	cameraLine->vertexArray[0].position = { centerPos.x, centerPos.y};
	cameraLine->vertexArray[1].position = { 11200.f, centerPos.y};
	cameraLine->vertexArray[2].position = { 11200.f, centerPos.y };
	cameraLine->vertexArray[3].position = { 13000.f, 650.f };
	cameraLine->vertexArray[4].position = { 13000.f, 650.f };
	cameraLine->vertexArray[5].position = { 15600.f, 650.f };
	cameraLine->vertexArray[0].color = sf::Color::Red;
	cameraLine->vertexArray[1].color = sf::Color::Red;
	cameraLine->vertexArray[2].color = sf::Color::Red;
	cameraLine->vertexArray[3].color = sf::Color::Red;
	cameraLine->vertexArray[4].color = sf::Color::Red;
	cameraLine->vertexArray[5].color = sf::Color::Red;

	AddGo(square);
	AddGo(cameraLine);

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
	worldView.setCenter(player->GetPosition().x, player->GetPosition().y - 150.f);

	CheckBlockCollision(dt);
	CheckLineCollision();

		
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();

	mousePos = ScreenToWorldPos(mousePos);
	
	std::cout << mousePos.x << ", " << mousePos.y << std::endl;
}

void Stage1_1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	//drawGrid(window, 20, 20);
}

void Stage1_1::CheckBlockCollision(float dt)
{
	Block* block;
	for (int i = 0; i < 8; i++)
	{
		std::string name = "Block";
		std::string num = std::to_string(i + 1);

		block = (Block*)FindGo(name + num);
		sf::FloatRect blockRect = block->GetGlobalBounds();
		
		player->WallCollision(blockRect);
	}
}

void Stage1_1::CheckLineCollision()
{
	VertexArrayGo* square = (VertexArrayGo*)FindGo("SlopeLine");

	player->LineCollision(square->vertexArray[0].position, square->vertexArray[1].position);
}
