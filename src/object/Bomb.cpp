/* 
 * File:   Bomb.cpp
 * Author: svirch_n
 * 
 * Created on 03 June 2014, 13:41
 */

#include "Bomb.hh"
#include "Fire.hh"

std::string const Bomb::Tag = "bomb";

static const double BOMBTIME = 2;

bool Bomb::initialize() {
    this->scale(glm::vec3(0.10, 0.10, 0.10));
    this->_position.y += 0.25;
    return true;
}

void Bomb::update(const gdl::Clock& clock, gdl::Input& input) {

    this->_time += clock.getElapsed();
    
    if (this -> _time >= BOMBTIME) {
        std::cout << "BOOM: " << this << std::endl;
        this -> die();
        this -> createFire();
    }
}

void Bomb::createFire() {
    
    Fire* obj = new Fire();
    
    obj->setStep(1);
    obj->setPosition(this->_position.x, this->_position.z);
    obj->setDirection(Fire::None);
    
    addObject(obj);
}