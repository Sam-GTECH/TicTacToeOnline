#include "State.h"

State::State()
{}

void State::create(GameManager* game, State* old_state) {}

void State::leave(GameManager* game) {}

bool State::preUpdate(GameManager* game) { return false; }
void State::postUpdate(GameManager* game) {}
bool State::preDraw(GameManager* game) { return false; }
void State::postDraw(GameManager* game) {}

void State::handleInput(GameManager* game, sf::Event event) {}