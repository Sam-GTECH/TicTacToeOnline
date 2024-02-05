#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class GameObject;

class GameManager
{
	public:
		sf::RenderWindow window;

		GameManager(int width, int height);
		~GameManager();
		
		void gameLoop();

		void onKeyInput();
		void update();
		void draw();

		void addChild(GameObject* obj);

	private:
		std::vector<GameObject*> children;
		bool run = true;
};