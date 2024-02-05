#include "GameManager.h"
#include "GameObject.h"
#include "Case.h"
#include "Grid.h"
#include "Utils.hpp"

#include <iostream>

GameManager::GameManager(int width, int height)
{
	window.create(sf::VideoMode(width, height), "Tic Tac Toe Online", sf::Style::Close);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    Grid* grid = new Grid();
    addChild(grid);
}

GameManager::~GameManager()
{
    window.~RenderWindow();
    for (int i = 0; i < children.size(); i++)
    {
        delete children[i];
    }
}

void GameManager::gameLoop()
{
	while (run && window.isOpen())
	{
        onKeyInput();

        update();

        draw();
	}
    return;
}

void GameManager::onKeyInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // évènement "fermeture demandée" : on ferme la fenêtre
        if (event.type == sf::Event::Closed)
        {
            run = false;
            break;
        }

        for (int i = 0; i < children.size(); i++)
        {
            children[i]->onKeyInput(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i m_pos = sf::Mouse::getPosition(window);
                if (Utils::pointOnObject(m_pos, children[i]))
                {
                    children[i]->onMouseClick();
                }
            }
        }
    }
}

void GameManager::update()
{
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->update();
    }
}

void GameManager::draw()
{
    window.clear(sf::Color(0, 0, 0));
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->draw(window);
    }
    window.display();
}

void GameManager::addChild(GameObject* obj)
{
    children.push_back(obj);
    obj->game = this;
    obj->parent = obj;
}