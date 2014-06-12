/* 
 * File:   Wall.cpp
 * Author: svirch_n
 * 
 * Created on 02 June 2014, 16:15
 */

#include "Wall.hh"
#include "ResourcesPath.hh"

std::string const Wall::Tag = "wall";

Wall::~Wall() {
}

bool Wall::initialize() {
    this->setSpeed(0);
    return this->setTexture(ResourcesPath::asset("textures/wall.tga"));
}


void Wall::update(gdl::Clock const &clock, gdl::Input &input)
{
    if (input.getKey(SDLK_UP))
        translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_DOWN))
        translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_LEFT))
        translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_RIGHT))
        translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);   
}
