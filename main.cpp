#include "GameManager.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main()
{
    GameManager* game = new GameManager(SCREEN_WIDTH, SCREEN_HEIGHT);

    game->gameLoop();

    delete game;

    /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }*/

    return 0;
} 