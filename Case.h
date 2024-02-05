#pragma once
#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Case : public GameObject
{
	public:
		Case(float x, float y);

		void setValue();
		sf::String getValue();

		void draw(sf::RenderWindow& window) override;
		void onMouseClick() override;

	private:
		sf::String value = "";
		sf::RectangleShape rect;

		int width = 60;
		int height = 60;
};