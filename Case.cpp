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
	if (value == 1)
	{
		sf::RectangleShape line(sf::Vector2f(20, 5));
		line.setPosition(getPos());
		line.setFillColor(sf::Color::Cyan);
		line.rotate(45);
		window.draw(line);
		sf::RectangleShape line2(sf::Vector2f(20, 5));
		line2.setPosition(getPos());
		line2.setFillColor(sf::Color::Cyan);
		line2.rotate(-45);
		window.draw(line2);
	}
	else if (value == 2)
	{
		sf::CircleShape circle(width - 30);
		circle.setPosition(getPos());
		circle.setOutlineColor(sf::Color::Red);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineThickness(10);
		window.draw(circle);
	}
}

void Case::onMouseClick()
{
	GameObject::onMouseClick();
	setValue(game->playerTurn);
	game->checkVictory();
}

void Case::setValue(int val)
{
	value = val;
}

int Case::getValue()
{
	return value;
}