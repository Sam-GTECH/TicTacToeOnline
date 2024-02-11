#pragma once

#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include <iostream>

namespace Utils
{
    bool pointOnObject(sf::Vector2f pos, GameObject* obj);
}