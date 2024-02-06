#include "GameObject.h"
#include "SFML/Window/Mouse.hpp"
#include "Utils.h"

#include <iostream>

GameObject::GameObject(float x, float y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}
GameObject::GameObject() {}

void GameObject::postInit() {
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->game = game;
	}
}

void GameObject::onKeyInput(sf::RenderWindow& window) {
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

void GameObject::onMouseClick()
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->onMouseClick();
	}
}

void GameObject::onMouseRelease()
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->onMouseRelease();
	}
}

void GameObject::update()
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->update();
	}
}

void GameObject::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->draw(window);
	}
}

sf::Vector2f GameObject::getPos()
{
	return sf::Vector2f(x, y);
}

sf::Vector2f GameObject::getSize()
{
	return sf::Vector2f(width, height);
}

void GameObject::addChild(GameObject* obj)
{
	children.push_back(obj);
	obj->game = game;
	obj->parent = this;
	obj->postInit();
}