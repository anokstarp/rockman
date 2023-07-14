#pragma once
#include "Scene.h"
#include "ObjectPool.h"

class Player;	

class Stage1_1 : public Scene
{
protected:
    Player* player;
    sf::Vector2f windowSize;
    sf::Vector2f centerPos;

public:
	Stage1_1();
	virtual ~Stage1_1() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;


    void drawGrid(sf::RenderWindow& win, int rows, int cols) {
        // initialize values
        int numLines = rows + cols - 2;
        sf::VertexArray grid(sf::Lines, 2 * (numLines));
        win.setView(win.getDefaultView());
        auto size = win.getView().getSize();
        float rowH = size.y / rows;
        float colW = size.x / cols;

        // row separators
        for (int i = 0; i < rows - 1; i++) {
            int r = i + 1;
            float rowY = rowH * r;
            grid[i * 2].position = { 0, rowY };
            grid[i * 2 + 1].position = { size.x, rowY };
        }

        // column separators
        for (int i = rows - 1; i < numLines; i++) {
            int c = i - rows + 2;
            float colX = colW * c;
            grid[i * 2].position = { colX, 0 };
            grid[i * 2 + 1].position = { colX, size.y };
        }

        // draw it
        win.draw(grid);
    }
};

