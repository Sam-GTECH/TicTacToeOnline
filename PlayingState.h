#pragma once
#include "State.h"

class PlayingState : public State
{
	public:
		PlayingState();

		bool preUpdate(GameManager* game) override;
		void postUpdate(GameManager* game) override;

		bool preDraw(GameManager* game) override;
		void postDraw(GameManager* game) override;
};