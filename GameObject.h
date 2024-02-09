#pragma once
#include "SFML\Graphics\RenderWindow.hpp"
#include "GameManager.h"

class GameObject
{
public:
	GameObject(float x, float y, int width, int height);
	GameObject();
	virtual void postInit();

	virtual void onKeyInput(sf::RenderWindow& window);
	virtual void onMouseClick();
	virtual void handleInput(GameManager* game, sf::Event event);
	virtual void update();
	virtual void draw(sf::RenderWindow& window);

	virtual void addChild(GameObject* obj);

	sf::Vector2f getPos();
	sf::Vector2f getSize();

	GameManager* game;
	GameObject* parent;
	State* state;

private:
	float x, y;
	int width, height;

protected:
	std::vector<GameObject*> children;
};