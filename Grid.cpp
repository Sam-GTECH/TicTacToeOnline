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