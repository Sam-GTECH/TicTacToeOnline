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
	/*if (value == 1)
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
		pos.x = pos.x + circle.getRadius()/2;
		pos.y = pos.y + circle.getRadius()/2;
		circle.setPosition(pos);
		circle.setOutlineColor(sf::Color::Red);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineThickness(5);
		window.draw(circle);
	}*/
}

/*void Case::onMouseClick()
{
	if (!is_pressed) {
		GameObject::onMouseClick();
		setValue(game->playerTurn);
		game->checkVictory();
	}
	is_pressed = true;
	game->case_is_pressed = true;
}

void Case::onMouseRelease()
{
	is_pressed = false;
}*/

void Case::handleInput(GameManager* game, sf::Event event)
{
	/*setValue()*/
}

void Case::setValue(int val)
{
	value = val;
}

int Case::getValue()
{
	return value;
}