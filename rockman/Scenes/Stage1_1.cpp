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
#include "ResourceMgr.h"
#include "BossMonster.h"
#include "NormalMonster.h"
#include "Monster.h"
#include "RectGo.h"

#define CHARACTER 4
#define MAP 1
#define MAPCHANGE 2
#define WALL 11

Stage1_1::Stage1_1()
	: Scene(SceneId::Stage1_1)
{
	RESOURCE_MGR.LoadFromCSVFile("Scripts/Stage1_1ResourceList.csv", true);
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
	player->sortLayer = CHARACTER;
	player->sortOrder = 3;

	hpBar = (RectGo*)AddGo(new RectGo("hpBar"));
	hpBar->rect.setFillColor(sf::Color::Green);
	hpBar->SetOrigin(Origins::BC);
	hpBar->SetPosition(50.f, FRAMEWORK.GetWindowSize().y * 0.6f);
	hpBar->sortLayer = 100;


	boss = (BossMonster*)AddGo(new BossMonster("", "boss"));
	boss->SetOrigin(Origins::BC);
	boss->SetPosition(16050.f, 950.f);
	boss->SetPlayer(player);
	boss->sortLayer = CHARACTER;


	for (int i = 0; i < 10; i++)
	{
		std::string num = std::to_string(i + 1);
		std::string name = "monster" + num;

		monster[i] = (NormalMonster*)AddGo(new NormalMonster("", name.c_str()));
		monster[i]->sprite.setScale(3.0, 3.0);
		monster[i]->SetPlayer(player);
		monster[i]->SetPosition(400.f + 830.f * (i + 1), 560.f);
		monster[i]->sortLayer = CHARACTER;
	}

	effectPool.OnCreate = [this](SpriteEffect* effect)
	{
		effect->SetDuration(3.f);
		effect->SetPool(&effectPool);
	};
	effectPool.Init();


	Block* block1 = (Block*)AddGo(new Block("Block1"));
	block1->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block1->SetOutlineColor(sf::Color::Red);
	block1->SetPosition(0, windowSize.y);
	block1->SetSize(11400.f, 135.f);
	block1->SetOrigin(Origins::BL);
	block1->SetBlockType(BlockType::Floor);
	block1->sortLayer = WALL;

	Block* block2 = (Block*)AddGo(new Block("Block2"));
	block2->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block2->SetOutlineColor(sf::Color::Red);
	block2->SetPosition(12950, 950.f);
	block2->SetSize(4000.f, 150.f);
	block2->SetOrigin(Origins::TL);
	block2->SetBlockType(BlockType::Floor);
	block2->sortLayer = WALL;

	Block* block3 = (Block*)AddGo(new Block("Block3"));
	block3->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block3->SetOutlineColor(sf::Color::Red);
	block3->SetPosition(5000, 550.f);
	block3->SetSize(50.f, 200.f);
	block3->SetOrigin(Origins::BL);
	block3->SetBlockType(BlockType::Breakable, player);
	block3->sortLayer = WALL;

	Block* block4 = (Block*)AddGo(new Block("Block4"));
	block4->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block4->SetOutlineColor(sf::Color::Red);
	block4->SetPosition(6550, 550.f);
	block4->SetSize(50.f, 200.f);
	block4->SetOrigin(Origins::BL);
	block4->SetBlockType(BlockType::Breakable, player);
	block4->sortLayer = WALL;

	Block* block5 = (Block*)AddGo(new Block("Block5"));
	block5->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block5->SetOutlineColor(sf::Color::Red);
	block5->SetPosition(8080, 550.f);
	block5->SetSize(50.f, 200.f);
	block5->SetOrigin(Origins::BL);
	block5->SetBlockType(BlockType::Breakable, player);
	block5->sortLayer = WALL;

	//Á¦ÀÏ Å«º®
	Block* block6 = (Block*)AddGo(new Block("Block6"));
	block6->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block6->SetOutlineColor(sf::Color::Red);
	block6->SetPosition(9600.f, 550.f);
	block6->SetSize(60.f, 500.f);
	block6->SetOrigin(Origins::BL);
	block6->SetBlockType(BlockType::UnClimbable, player);
	block6->sortLayer = WALL;

	//¸Ê ¿Ü°û ¿ÞÂÊ
	Block* block7 = (Block*)AddGo(new Block("Block7"));
	block7->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block7->SetOutlineColor(sf::Color::Red);
	block7->SetPosition(0.f, 0.f);
	block7->SetSize(500.f, 700.f);
	block7->SetOrigin(Origins::TR);
	block7->sortLayer = WALL;

	//º¸½º·ë À­º®
	Block* block8 = (Block*)AddGo(new Block("Block8"));
	block8->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block8->SetOutlineColor(sf::Color::Red);
	block8->SetPosition(15140.f, 750.f);
	block8->SetSize(100.f, 400.f);
	block8->SetOrigin(Origins::BL);
	block8->sortLayer = WALL;

	//º¸½º·ë ¿À¸¥ÂÊ º®
	Block* block9 = (Block*)AddGo(new Block("Block9"));
	block9->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block9->SetOutlineColor(sf::Color::Red);
	block9->SetPosition(16150.f, 950.f);
	block9->SetSize(100.f, 700.f);
	block9->SetOrigin(Origins::BL);
	block9->sortLayer = WALL;

	Block* block10 = (Block*)AddGo(new Block("Block10"));
	block10->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block10->SetOutlineColor(sf::Color::Red);
	block10->SetPosition(15200.f, 350.f);
	block10->SetSize(950.f, 100.f);
	block10->SetOrigin(Origins::BL);
	block10->sortLayer = WALL;

	//º¸½º·ë ¹®
	Block* door = (Block*)AddGo(new Block("Door"));
	door->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	door->SetOutlineColor(sf::Color::Red);
	door->SetPosition(15190.f, 866.f);
	door->sortLayer = MAPCHANGE;
	door->SetBlockType(BlockType::Door);

	SpriteGo* map = (SpriteGo*)AddGo(new SpriteGo("graphics/map1_1.png", "map"));
	map->SetPosition(0, 0);
	map->sprite.setScale(3, 3);
	map->sortLayer = MAP;

	SpriteGo* firstDoor = (SpriteGo*)AddGo(new SpriteGo("graphics/firstDoor.png", "firstDoor"));
	firstDoor->SetPosition(0, 0);
	firstDoor->sprite.setScale(3, 3);
	firstDoor->sortLayer = MAPCHANGE;
	firstDoor->SetActive(false);

	SpriteGo* secondDoor = (SpriteGo*)AddGo(new SpriteGo("graphics/secondDoor.png", "secondDoor"));
	secondDoor->SetPosition(0, 0);
	secondDoor->sprite.setScale(3, 3);
	secondDoor->sortLayer = MAPCHANGE;
	secondDoor->SetActive(false);

	SpriteGo* thirdDoor = (SpriteGo*)AddGo(new SpriteGo("graphics/thirdDoor.png", "thirdDoor"));
	thirdDoor->SetPosition(0, 0);
	thirdDoor->sprite.setScale(3, 3);
	thirdDoor->sortLayer = MAPCHANGE;
	thirdDoor->SetActive(false);

	SpriteGo* fourthDoor = (SpriteGo*)AddGo(new SpriteGo("graphics/fourthDoor.png", "fourthDoor"));
	fourthDoor->SetPosition(0, 0);
	fourthDoor->sprite.setScale(3, 3);
	fourthDoor->sortLayer = MAPCHANGE;
	fourthDoor->SetActive(false);


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


	VertexArrayGo* cameraLine = new VertexArrayGo("", "CameraLine");
	cameraLine->vertexArray.resize(8);
	cameraLine->sortLayer = 5;
	cameraLine->vertexArray.setPrimitiveType(sf::Lines);
	cameraLine->vertexArray[0].position = { centerPos.x, centerPos.y};
	cameraLine->vertexArray[1].position = { 11200.f, centerPos.y};
	cameraLine->vertexArray[2].position = { 11200.f, centerPos.y };
	cameraLine->vertexArray[3].position = { 12500.f, 680.f };
	cameraLine->vertexArray[4].position = { 12500.f, 680.f };
	cameraLine->vertexArray[5].position = { 15200.f, 680.f };
	cameraLine->vertexArray[0].color = sf::Color::Red;
	cameraLine->vertexArray[1].color = sf::Color::Red;
	cameraLine->vertexArray[2].color = sf::Color::Red;
	cameraLine->vertexArray[3].color = sf::Color::Red;
	cameraLine->vertexArray[4].color = sf::Color::Red;
	cameraLine->vertexArray[5].color = sf::Color::Red;

	cameraLine->vertexArray[6].position = { 15200.f, 680.f };
	cameraLine->vertexArray[7].position = { 15650.f, 680.f };
	cameraLine->vertexArray[6].color = sf::Color::Green;
	cameraLine->vertexArray[7].color = sf::Color::Green;

	AddGo(square);
	AddGo(cameraLine);

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void Stage1_1::Release()
{
	poolBullets.Release();
	effectPool.Release();

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

void Stage1_1::Reset()
{
}

void Stage1_1::Update(float dt)
{
	Scene::Update(dt);
	worldView.setCenter(CameraPosition());
	//worldView.setCenter(player->GetPosition().x, player->GetPosition().y - 150.f);

	hpBar->rect.setSize({ 20.f, 200.f * player->GetHp() / 100 });
	hpBar->SetOrigin(Origins::BC);

	CheckBlockCollision(dt);
	CheckLineCollision();
	ManageWall();
		
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
	{
		std::cout << "3¹ø ´­¸²" << std::endl;
		SCENE_MGR.ChangeScene(SceneId::Stage1_1);
	}


	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();

	mousePos = ScreenToWorldPos(mousePos);
	
	//std::cout << mousePos.x << ", " << mousePos.y << std::endl;
}

void Stage1_1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	//drawGrid(window, 20, 20);
}

void Stage1_1::CheckBlockCollision(float dt)
{
	Block* block;
	for (int i = 0; i < 10; i++)
	{
		std::string name = "Block";
		std::string num = std::to_string(i + 1);

		block = (Block*)FindGo(name + num);

		player->WallCollision(block);
	}

	block = (Block*)FindGo("Door");
	if (!block->doorOpen)
	{
		player->WallCollision(block);
	}
}

void Stage1_1::CheckLineCollision()
{
	VertexArrayGo* square = (VertexArrayGo*)FindGo("SlopeLine");

	player->LineCollision(square->vertexArray[0].position, square->vertexArray[1].position);
}

sf::Vector2f Stage1_1::CameraPosition()
{
	VertexArrayGo* line = (VertexArrayGo*)FindGo("CameraLine");
	sf::Vector2f playerCenter = player->GetCharCenter();
	sf::Vector2f CameraPos;

	if (playerCenter.x < line->vertexArray[0].position.x)
	{
		CameraPos.x = line->vertexArray[0].position.x;
		CameraPos.y = line->vertexArray[0].position.y;
	}
	else if (playerCenter.x > line->vertexArray[0].position.x && playerCenter.x < line->vertexArray[1].position.x)
	{
		CameraPos.x = playerCenter.x;
		CameraPos.y = Utils::LineEquation(line->vertexArray[0].position, line->vertexArray[1].position, playerCenter.x);
	}
	else if (playerCenter.x > line->vertexArray[2].position.x && playerCenter.x < line->vertexArray[3].position.x)
	{
		CameraPos.x = playerCenter.x;
		CameraPos.y = Utils::LineEquation(line->vertexArray[2].position, line->vertexArray[3].position, playerCenter.x);
	}
	else if (playerCenter.x > line->vertexArray[4].position.x && playerCenter.x < line->vertexArray[5].position.x)
	{
		CameraPos.x = playerCenter.x;
		CameraPos.y = Utils::LineEquation(line->vertexArray[4].position, line->vertexArray[5].position, playerCenter.x);
	}
	else if (playerCenter.x > line->vertexArray[6].position.x && playerCenter.x < line->vertexArray[7].position.x)
	{
		CameraPos.x = line->vertexArray[7].position.x;
		CameraPos.y = line->vertexArray[7].position.y;
	}
	else
	{
		CameraPos.x = line->vertexArray[7].position.x;
		CameraPos.y = line->vertexArray[7].position.y;
	}
	return CameraPos;
}

void Stage1_1::ManageWall()
{
	//¹«Á¶°Ç ¼öÁ¤ÇØ¾ßµÊ
	//#########################################################################
	Block* block;
	for (int i = 0; i < 8; i++)
	{
		std::string name = "Block";
		std::string num = std::to_string(i + 1);

		block = (Block*)FindGo(name + num);

		if (i == 2)
		{
			if (block->isBroken)
			{
				SpriteGo* door = (SpriteGo*)FindGo("firstDoor");
				door->SetActive(true);
			}
		}
		if (i == 3)
		{
			if (block->isBroken)
			{
				SpriteGo* door = (SpriteGo*)FindGo("secondDoor");
				door->SetActive(true);
			}
		}
		if (i == 4)
		{
			if (block->isBroken)
			{
				SpriteGo* door = (SpriteGo*)FindGo("thirdDoor");
				door->SetActive(true);
			}
		}
		if (i == 5)
		{
			if (block->isBroken)
			{
				SpriteGo* door = (SpriteGo*)FindGo("fourthDoor");
				door->SetActive(true);
			}
		}
	}
}

void Stage1_1::ObejectDie(Monster* monster)
{
	SpriteEffect* effect = effectPool.Get();
	effect->SetPosition(monster->GetPosition());
	effect->type = Effect::Boom;
	effect->sortLayer = CHARACTER;
	AddGo(effect);

	RemoveGo(monster);
}

void Stage1_1::BoomEffect(Monster* monster)
{
	SpriteEffect* effect = effectPool.Get();
	sf::FloatRect bound = monster->sprite.getGlobalBounds();
	float x = Utils::RandomRange(bound.left, bound.left + bound.width);
	float y = Utils::RandomRange(bound.top, bound.top + bound.height);

	effect->SetPosition(x, y);
	effect->type = Effect::Boom;
	effect->sortLayer = CHARACTER;
	AddGo(effect);
}

void Stage1_1::Boom(Bullet* bullet)
{
	SpriteEffect* effect = effectPool.Get();
	effect->SetPosition(bullet->GetPosition());
	effect->type = Effect::Boom;
	effect->sortLayer = CHARACTER;
	AddGo(effect);
}

void Stage1_1::AttackEffect(Monster* monster)
{
	SpriteEffect* effect = effectPool.Get();
	effect->SetPosition(monster->player->saber->GetPosition());
	effect->type = Effect::Attack;
	effect->Dir = monster->player->sprite.getScale().x;
	effect->sortLayer = CHARACTER;
	AddGo(effect);
}

void Stage1_1::BlockAttackEffect(Block* block)
{
	SpriteEffect* effect = effectPool.Get();
	effect->SetPosition(block->player->saber->GetPosition());
	effect->type = Effect::Attack;
	effect->Dir = block->player->sprite.getScale().x;
	effect->sortLayer = CHARACTER;
	AddGo(effect);
}

void Stage1_1::PlayerRecall(Player* player)
{
}
