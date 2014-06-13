/* 
 * File:   Box.cpp
 * Author: svirch_n
 * 
 * Created on 02 June 2014, 19:35
 */

#include "Box.hh"
#include "ResourcesPath.hh"

std::string const Box::Tag = "box";

Box::Box(): ACube("box") {
}

Box::~Box() {
}

bool Box::initialize() {
    this->setSpeed(10);
    this->scale(glm::vec3(0.8, 0.8, 0.8));
    return this->setTexture(ResourcesPath::asset("textures/box.tga"));
}

void Box::update(gdl::Clock const &clock, gdl::Input &input)
{
    this->saveCurrentState();
    if (input.getKey(SDLK_UP))
        translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_DOWN))
        translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_LEFT))
        translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_RIGHT))
        translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
}

void Box::onCollision(AGameObject& obj) {
    if (obj.getType() == "wall")
        this->restoreLastState(obj);
}
