#include "PlayingState.h"
#include "Utils.h"
#include "Case.h"

PlayingState::PlayingState() {}

void PlayingState::create(GameManager* game)
{
    game->addChild(grid);
}

void PlayingState::leave(GameManager* game) {}

bool PlayingState::preUpdate(GameManager* game)
{
    return false;
}

void PlayingState::postUpdate(GameManager* game)
{
    grid->update();
}

bool PlayingState::preDraw(GameManager* game) { return false; };
void PlayingState::postDraw(GameManager* game)
{
    grid->draw(game->window);
}

void PlayingState::handleInput(GameManager* game, sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        for (int i = 0; i < grid->cases.size(); i++)
        {
            Case* obj = grid->cases[i];
            if (Utils::pointOnObject(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), obj))
            {
                obj->handleInput(game, event, this);
                checkVictory(game);
            }
        }
    }
}

void PlayingState::changePlayerTurn()
{
    playerTurn = playerTurn == 1 ? 2 : 1;
}

void PlayingState::checkVictory(GameManager* game)
{
    if (!grid->checkVictory(this))
        changePlayerTurn();
    else
        game->setState("VICTORY", true);
}