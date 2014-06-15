/* 
 * File:   APlayer.cpp
 * Author: svirch_n
 *
 * Created on 15 June 2014, 13:15
 */

#include "APlayer.hh"
#include "Bomb.hh"

bool APlayer::initialize() {
    this->setSpeed(5);
    this->initAnim();
    this->scale(glm::vec3(0.0025, 0.0025, 0.0025));
    return true;
}

void APlayer::putBomb(){
    
    AGameObject* bomb = new Bomb();
    
    bomb->setPosition(glm::vec3(static_cast<int>(this->_position.x + 0.5),
                                0,
                                static_cast<int>(this->_position.z + 0.5)));
    bomb->setParent(getType());
    this->addObject(bomb);
}

void APlayer::onUpPressed(gdl::Clock const &clock)
{
    translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
    this -> lookNorth();
}

void APlayer::onDownPressed(gdl::Clock const &clock)
{
    translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
    this -> lookSouth();
}

void APlayer::onLeftPressed(gdl::Clock const &clock)
{
    translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    this -> lookWest();
}

void APlayer::onRightPressed(gdl::Clock const &clock)
{
    translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    this -> lookEast();
}

static const double COLLIDER_SIZE = 0.7;

Rectangle APlayer::getCollider() const {
    return Rectangle(
        this->_position.x + 0.5 - COLLIDER_SIZE / 2,
        this->_position.z + 0.5 - COLLIDER_SIZE / 2,
        COLLIDER_SIZE,
        COLLIDER_SIZE);
}

void APlayer::stop() {
    _model.setCurrentSubAnim("stop", false);
}

void APlayer::run() {
    _model.setCurrentSubAnim("run");
}
