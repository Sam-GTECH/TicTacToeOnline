#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "State.h"

class GameObject;
class OnlineManager;

class GameManager
{
	public:
		GameManager();
		~GameManager();

		bool Init(int width, int height);
		void Uninit();
		bool Connect();

		void gameLoop();

		void handleInput();
		void update();
		void draw();

		void addChild(GameObject* obj);

		void setState(std::string newState, bool push);
		void setState(std::string newState);
		std::string getState();
		bool isActiveState(State* state);

public:
		std::map<std::string, State*> states;
		std::vector<State*> state_process;

		OnlineManager* onlineManage;

		sf::Font font;

		sf::RenderWindow window;
		int victory = 0;

		bool case_is_pressed = false;

	private:
		std::vector<GameObject*> children;
		bool run = true;

		std::string current_state;
};