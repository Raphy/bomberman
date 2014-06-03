/* 
 * File:   Bomb.cpp
 * Author: svirch_n
 * 
 * Created on 03 June 2014, 13:41
 */

#include "Bomb.hh"

void Bomb::update(const gdl::Clock& clock, gdl::Input& input) {

    if (input.getKey(SDLK_UP))
        translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_DOWN))
        translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_LEFT))
        translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_RIGHT))
        translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
}
