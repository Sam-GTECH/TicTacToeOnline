#pragma once
#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>
#include "SFML/System.hpp"
#include "GameObject.h"
#include "PlayingState.h"

class Case : public GameObject
{
	public:
		Case(float x, float y);

		void setValue(int val);
		int getValue();

		void draw(sf::RenderWindow& window) override;
		void handleInput(GameManager* game, sf::Event event, PlayingState* state);
		/*void onMouseClick() override;*/

	private:
		int value = 0;
		sf::RectangleShape rect;

		sf::RectangleShape line1;
		sf::RectangleShape line2;
		sf::CircleShape circle;

		int width = 60;
		int height = 60;

		bool is_pressed = false;
};