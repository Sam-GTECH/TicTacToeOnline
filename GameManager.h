#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class GameObject;
class Grid;

class GameManager
{
	public:
		sf::RenderWindow window;
		int playerTurn = 1;
		int victory = 0;

		Grid* grid;

		GameManager(int width, int height);
		~GameManager();

		void changePlayerTurn();
		void checkVictory();
		
		void gameLoop();

		void onKeyInput();
		void update();
		void draw();

		void addChild(GameObject* obj);

	private:
		std::vector<GameObject*> children;
		bool run = true;
		bool is_pressed = false;
};