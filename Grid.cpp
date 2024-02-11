#include "Grid.h"
#include "Case.h"

Grid::Grid() : GameObject()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Case* c = new Case(160 + (100 * j), 80 + (100 * i));
            addChild(c);
        }
    }
}

void Grid::addChild(GameObject* obj)
{
    GameObject::addChild(obj);
    cases.push_back(dynamic_cast<Case*>(obj));
}

bool Grid::checkVictory()
{
    int count = 0;
    int player = game->playerTurn; // 0, 1, 2 | 3, 4, 5 | 6, 7, 8
    
    // horizontal check
    for (int i = 0; i < 8; i = i+3)
    {
        if (cases[i]->getValue() == player && cases[i+1]->getValue() == player && cases[i+2]->getValue() == player)
        {
            return true;
        }
    }

    // vertical check
    for (int i = 0; i < 3; i++)
    {
        if (cases[i]->getValue() == player && cases[i + 3]->getValue() == player && cases[i + 6]->getValue() == player)
        {
            return true;
        }
    }

    // Diagonal checks
    if (cases[0]->getValue() == player && cases[4]->getValue() == player && cases[8]->getValue() == player)
    {
        return true;
    }

    if (cases[2]->getValue() == player && cases[4]->getValue() == player && cases[6]->getValue() == player)
    {
        return true;
    }

    return false; 
}