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
    this->scale(glm::vec3(0.8, 0.8, 0.8));
    return this->setTexture(ResourcesPath::asset("textures/box.tga"));
}

void Box::update(gdl::Clock const &clock, gdl::Input &input)
{}

void Box::onCollision(AGameObject& obj) {
    if (obj.getType() == "fire"
        && obj.getPosition() == this->getPosition())
        this->die();
    else if (obj.getType() == "wall")
        this->restoreLastState();
}
