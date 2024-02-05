#pragma once
#include "GameObject.h"

class Case;

class Grid : public GameObject
{
	public:
		Grid();

		bool checkVictory();
		void addChild(GameObject* obj) override;

	protected:
		std::vector<Case*> cases;
};