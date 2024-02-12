#include "GameManager.h"
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main()
{

    
        GameManager* game = new GameManager;
        game->Init(SCREEN_WIDTH, SCREEN_HEIGHT);

        game->gameLoop();

        game->Uninit();
        delete game;
    

    return 0;
} 