#pragma once
#include "GameObject.h"

class PlayingState;
class Case;

class Grid : public GameObject
{
	public:
		std::vector<Case*> cases;

		Grid();

		bool checkVictory(PlayingState* state);
		void addChild(GameObject* obj) override;
};