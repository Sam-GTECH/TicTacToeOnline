#include "Utils.h"

bool Utils::pointOnObject(sf::Vector2i pos, GameObject* obj)
{
    int p_x = pos.x;
    int p_y = pos.y;

    sf::Vector2i vect_pos = obj->getPos();
    int o_x = vect_pos.x;
    int o_y = vect_pos.y;
    sf::Vector2i vect_size = obj->getSize();
    int o_w = vect_size.x;
    int o_h = vect_size.y;

    std::cout << o_x << "/" << o_y << "/" << o_w << "/" << o_h << "/" << std::endl;
    std::cout << p_x << "/" << p_y << std::endl;


    return p_x > o_x &&
        p_x < o_x + o_w &&
        p_y > o_y &&
        p_y < o_y + o_h;
}