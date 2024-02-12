#include "GameManager.h"
#include "OnlineManager.h"
#include "GameObject.h"
#include "Case.h"

#include "Utils.h"
#include "json.hpp"

#include "PlayingState.h"
#include "VictoryState.h"

#include <iostream>


GameManager::GameManager()
{
    onlineManage = nullptr;
}

GameManager::~GameManager()
{
    assert(children.size()==0);
}

bool GameManager::Init(int width, int height)
{
    window.create(sf::VideoMode(width, height), "Tic Tac Toe Online", sf::Style::Close);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    font.loadFromFile("arialbd.ttf");

    states["PLAYING"] = new PlayingState();
    states["VICTORY"] = new VictoryState();

    onlineManage = new OnlineManager();
    Connect();
    onlineManage->createWindow();

    setState("PLAYING");
    return true;
}

void GameManager::Uninit()
{
    for (int i = 0; i < children.size(); i++)
    {
        delete children[i];
    }
    children.clear();
}

bool GameManager::Connect()
{
    onlineManage->connect();
    return true;
}

void GameManager::gameLoop()
{
	while (run && window.isOpen())
	{

        handleInput();

        update();

        draw();
	}
    
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

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {    
            onlineManage->sendMessage("test");
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
    obj->state = states[getState()];
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
    State* old_state = states[getState()];
    state_process.push_back(states[newState]);
    states[newState]->create(this, old_state);
}
void GameManager::setState(std::string newState)
{
    State* old_state = states[getState()];
    state_process.push_back(states[newState]);
    states[newState]->create(this, old_state);
}

std::string GameManager::getState()
{
    if (state_process.size() == 0)
        return "";
    for (const auto& pair : states) {
        if (pair.second == state_process.back())
            return pair.first;
    }
}

bool GameManager::isActiveState(State* state)
{
    return state == states[getState()];
}


