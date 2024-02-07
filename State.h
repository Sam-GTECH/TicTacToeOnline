#pragma once
#include "GameManager.h"

class State
{
	public:
		virtual void handleInput(GameManager* game, sf::Event event);

		virtual bool preUpdate(GameManager* game);
		virtual void postUpdate(GameManager* game);

		virtual bool preDraw(GameManager* game);
		virtual void postDraw(GameManager* game);
};