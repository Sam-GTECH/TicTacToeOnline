#pragma once
#include "SFML/Window/Event.hpp"

class GameManager;

class State
{
	public:
		State();
		virtual void create(GameManager* game);
		virtual void leave(GameManager* game);

		virtual void handleInput(GameManager* game, sf::Event event);

		virtual bool preUpdate(GameManager* game);
		virtual void postUpdate(GameManager* game);

		virtual bool preDraw(GameManager* game);
		virtual void postDraw(GameManager* game);
};