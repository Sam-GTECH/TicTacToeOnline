#include "Case.h"
#include <iostream>

Case::Case(float x, float y) : GameObject(x, y, 120, 120)
{
	rect.setPosition(x, y);
	rect.setSize(sf::Vector2f(100, 100));
	rect.setOutlineColor(sf::Color(255, 255, 255, 255));
	rect.setOutlineThickness(5);
	rect.setFillColor(sf::Color(0, 0, 0, 255));
}

void Case::draw(sf::RenderWindow& window)
{
	window.draw(rect);
}

void Case::onMouseClick()
{
	GameObject::onMouseClick();
	std::cout << "Hey" << std::endl;
}