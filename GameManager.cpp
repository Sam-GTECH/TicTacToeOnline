#include "GameManager.h"
#include "GameObject.h"
#include "Case.h"
#include "Grid.h"
#include "Utils.h"

#include <iostream>

GameManager::GameManager(int width, int height)
{
	window.create(sf::VideoMode(width, height), "Tic Tac Toe Online", sf::Style::Close);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    Grid* g = new Grid();
    addChild(g);
    grid = g;
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
    while (victory > 0)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                victory = 0;
        }
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
                if (Utils::pointOnObject(sf::Vector2f(m_pos.x, m_pos.y), children[i]))
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
    obj->postInit();
}

void GameManager::changePlayerTurn()
{
    playerTurn = playerTurn == 1 ? 2 : 1;
}

void GameManager::checkVictory()
{
    if (!grid->checkVictory())
        changePlayerTurn();
    else
    {
        run = false;
        victory = playerTurn;
    }
}