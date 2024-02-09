#pragma once
#include "State.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

class VictoryState : public State
{
	public:
		VictoryState();
		void create(GameManager* game, State* old_state) override;

		void postDraw(GameManager* game) override;

	private:
		sf::RectangleShape rect;

		sf::Text text;
};