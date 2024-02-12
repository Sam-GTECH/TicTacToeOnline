#include "Case.h"
#include <iostream>

Case::Case(float x, float y) : GameObject(x, y, 120, 120)
{
	rect.setPosition(x, y);
	rect.setSize(sf::Vector2f(100, 100));
	rect.setOutlineColor(sf::Color(255, 255, 255, 255));
	rect.setOutlineThickness(5);
	rect.setFillColor(sf::Color(0, 0, 0, 255));

	// Cross
	sf::Vector2f pos = getPos();
	pos.x = pos.x + width / 2;
	pos.y = pos.y + height / 2;
	line1.setPosition(pos);
	line1.setSize(sf::Vector2f(20, 5));
	line1.setFillColor(sf::Color::Cyan);
	line1.rotate(45);

	pos.x = pos.x + 5;
	pos.y = pos.y + 2.5;
	line2.setPosition(pos);
	line2.setSize(sf::Vector2f(20, 5));
	line2.setFillColor(sf::Color::Cyan);
	line2.rotate(-45);

	// Circle
	pos = getPos();
	circle.setPosition(getPos());
	circle.setRadius(width - 30);
	circle.setOutlineColor(sf::Color::Red);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(5);
}

void Case::draw(sf::RenderWindow& window)
{
	window.draw(rect);
	if (value == 1)
	{
		window.draw(line1);
		window.draw(line2);
	}
	else if (value == 2)
	{
		window.draw(circle);
	}
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

void Case::handleInput(GameManager* game, sf::Event event, PlayingState* state)
{
	setValue(state->playerTurn);
}

void Case::setValue(int val)
{
	//if (value > 0) return;
	value = val;
}

int Case::getValue()
{
	return value;
}