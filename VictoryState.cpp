#include "VictoryState.h"
#include "GameManager.h"

VictoryState::VictoryState() {}

void VictoryState::create(GameManager* game, State* old_state)
{
	rect.setFillColor(sf::Color(0, 0, 0, 255 / 2));
	rect.setSize(sf::Vector2f(game->window.getSize()));

	text.setFont(game->font);
	text.setString("GAME OVER YEAH");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
}

void VictoryState::postDraw(GameManager* game)
{
	game->window.draw(rect);
	game->window.draw(text);
}