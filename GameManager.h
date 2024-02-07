#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "State.h"

class GameObject;
class Grid;

class GameManager
{
	public:

		std::map<std::string, State*> states;
		std::vector<State*> state_process;

		sf::RenderWindow window;
		int playerTurn = 1;
		int victory = 0;

		bool case_is_pressed = false;

		Grid* grid;

		GameManager(int width, int height);
		~GameManager();

		void changePlayerTurn();
		void checkVictory();
		
		void gameLoop();

		void handleInput();
		void update();
		void draw();

		void addChild(GameObject* obj);

		void setState(std::string newState, bool push);
		void setState(std::string newState);
		std::string getState();

	private:
		std::vector<GameObject*> children;
		bool run = true;
		bool is_pressed = false;

		std::string current_state;
};