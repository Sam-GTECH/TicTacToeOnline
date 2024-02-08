#include "GameManager.h"
#include "GameObject.h"
#include "Case.h"

#include "Utils.h"
#include "json.hpp"

#include "PlayingState.h"

#include <iostream>

using json = nlohmann::json;

GameManager::GameManager(int width, int height)
{
	window.create(sf::VideoMode(width, height), "Tic Tac Toe Online", sf::Style::Close);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    states["PLAYING"] = new PlayingState();

    setState("PLAYING");
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

        handleInput();

        update();

        draw();
	}
    /*while (victory > 0)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                victory = 0;
        }
    }*/
    return;
}

void GameManager::handleInput()
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

        states[getState()]->handleInput(this, event);
    }
}

void GameManager::update()
{
    if (states[getState()]->preUpdate(this))
        return;

    for (int i = 0; i < children.size(); i++)
    {
        children[i]->update();
    }

    states[getState()]->postUpdate(this);
}

void GameManager::draw()
{
    window.clear(sf::Color(0, 0, 0));

    if (states[getState()]->preDraw(this))
        return;

    for (int i = 0; i < children.size(); i++)
    {
        children[i]->draw(window);
    }

    for (int i = 0; i < state_process.size(); i++)
    {
        state_process[i]->postDraw(this);
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

void GameManager::setState(std::string newState, bool push)
{
    if (!push)
    {
        for (int i = 0; i < state_process.size(); i++)
        {
            state_process[i]->leave(this);
        }
        state_process.clear();
    }
    state_process.push_back(states[newState]);
    states[newState]->create(this);
}
void GameManager::setState(std::string newState)
{
    state_process.push_back(states[newState]);
}

std::string GameManager::getState()
{
    for (const auto& pair : states) {
        if (pair.second == state_process.back())
            return pair.first;
    }
}

bool GameManager::isActiveState(State* state)
{
    return state == states[getState()];
}