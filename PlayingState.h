#pragma once
#include "State.h"
#include "Grid.h"

class Grid;

class PlayingState : public State
{
	public:
		PlayingState();
		void create(GameManager* game);
		void leave(GameManager* game);

		bool preUpdate(GameManager* game) override;
		void postUpdate(GameManager* game) override;

		bool preDraw(GameManager* game) override;
		void postDraw(GameManager* game) override;

		void handleInput(GameManager* game, sf::Event event) override;

		void changePlayerTurn();
		void checkVictory(GameManager* game);

		int playerTurn = 1;

	private:
		Grid* grid = new Grid();
};