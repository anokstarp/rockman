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
	block1->SetSize(11400.f, 150.f);
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

	//제일 큰벽
	Block* block6 = (Block*)AddGo(new Block("Block6"));
	block6->SetFillColor(sf::Color::Color(0, 0, 0, 0));
	block6->SetOutlineColor(sf::Color::Red);
	block6->SetPosition(9600.f, 550.f);
	block6->SetSize(60.f, 500.f);
	block6->SetOrigin(Origins::BL);
	block6->sortLayer = 10;

	SpriteGo* map = (SpriteGo*)AddGo(new SpriteGo("graphics/map1_1.png", "map"));
	map->SetPosition(0, 0);
	map->sprite.setScale(3, 3);
	map->sortLayer = 0;

	VertexArrayGo* background = new VertexArrayGo("", "Slope");
	background->vertexArray.resize(4);
	background->sortLayer = 5;
	background->vertexArray.setPrimitiveType(sf::Quads);
	background->vertexArray[0].position = { 11400, windowSize.y - 150.f };
	background->vertexArray[1].position = { 12950, 950 };
	background->vertexArray[2].position = { 12950, 1050 };
	background->vertexArray[3].position = { 11400, 660 };


	VertexArrayGo* square = new VertexArrayGo("", "SlopeLine");
	square->vertexArray.resize(4);
	square->sortLayer = 5;
	square->vertexArray.setPrimitiveType(sf::LinesStrip);
	square->vertexArray[0].position = { 11400, windowSize.y - 150.f };
	square->vertexArray[1].position = { 12950, 950 };
	square->vertexArray[2].position = { 12950, 1050 };
	square->vertexArray[3].position = { 11400, 660 };
	square->vertexArray[0].color = sf::Color::Red;
	square->vertexArray[1].color = sf::Color::Red;
	square->vertexArray[2].color = sf::Color::Red;
	square->vertexArray[3].color = sf::Color::Red;

	AddGo(background);
	AddGo(square);

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

	//Block* block = (Block*)FindGo("Block1");
	//int Collide = block->CheckCollision(player->GetBounds());
	//sf::FloatRect blockRect = block->GetGlobalBounds();
	//
	//switch (Collide)
	//{
	//case 1: //오른쪽
	//	player->SetPosition(blockRect.left + blockRect.width, player->GetPosition().y);
	//	break;
	//case 2: //왼쪽
	//	player->SetPosition(blockRect.left, player->GetPosition().y);
	//	break;
	//case 3: //아래
	//	player->SetPosition(player->GetPosition().x, blockRect.top + blockRect.height);
	//	break;
	//case 4: //위에
	//	player->SetPosition(player->GetPosition().x, blockRect.top);
	//	player->OnGround();
	//	//isJump = false;
	//	break;
	//}

	//Block* block2 = (Block*)FindGo("Block2");
	//Collide = block2->CheckCollision(player->GetBounds());
	//blockRect = block2->GetGlobalBounds();

	//switch (Collide)
	//{
	//case 1: //오른쪽
	//	player->SetPosition(blockRect.left + blockRect.width, player->GetPosition().y);
	//	break;
	//case 2: //왼쪽
	//	player->SetPosition(blockRect.left, player->GetPosition().y);
	//	break;
	//case 3: //아래
	//	player->SetPosition(player->GetPosition().x, blockRect.top + blockRect.height);
	//	break;+
	//case 4: //위에
	//	player->SetPosition(player->GetPosition().x, blockRect.top);
	//	player->OnGround();
	//	//isJump = false;
	//	break;
	//}
	CheckBlockCollision(dt);
		
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
	sf::Vector2f curPos = player->GetPosition();

	for (int i = 0; i < 6; i++)
	{
		std::string name = "Block";
		std::string num = std::to_string(i + 1);

		block = (Block*)FindGo(name + num);
		sf::FloatRect blockRect = block->GetGlobalBounds();
		sf::FloatRect playerRect = player->sprite.getGlobalBounds();
		

		switch (block->CheckCollision(playerRect))
		{
		case 1: //벽 오른쪽 닿아있다 
			if (!wallJumpLeft)
				player->SetPosition(blockRect.left + blockRect.width + playerRect.width * 0.5f, player->GetPosition().y);

			//벽에 붙어있는데 왼쪽 꾹 누르고 있는경우
			if (INPUT_MGR.GetKey(sf::Keyboard::Left))
			{
				//속도 늦춰야됨
				player->ySpeed = -60;
				player->Drag(dt);
				//벽 점프
				if (INPUT_MGR.GetKeyDown(sf::Keyboard::X))
				{
					wallJumpRight = true;
				}
			}
			break;
		case 2: //벽 왼쪽 닿아있다.
			if (!wallJumpRight)
				player->SetPosition(blockRect.left - playerRect.width * 0.5f, player->GetPosition().y);

			//벽에 붙어있는데 오른쪽 누르고 있는 경우
			if (INPUT_MGR.GetKey(sf::Keyboard::Right))
			{
				//속도 늦춰야함
				player->ySpeed = -60;
				player->Drag(dt);

				//벽점프
				if (INPUT_MGR.GetKeyDown(sf::Keyboard::X))
				{

					wallJumpLeft = true;
				}
			}
			break;
		case 3: //아래
			player->SetPosition(player->GetPosition().x, blockRect.top + blockRect.height);
			//뚝 떨궈야함

			break;
		case 4: //위에
			player->SetPosition(player->GetPosition().x, blockRect.top);
			player->OnGround();
			//isJump = false;
			break;
		default:
			break;
		}
	}
}