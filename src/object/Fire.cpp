/*
 * File:   Fire.cpp
 * Author: svirch_n
 *
 * Created on 13 June 2014, 14:00
 */

#include "Fire.hh"
#include "ResourcesPath.hh"

bool Fire::initialize()
{
    this -> scale(glm::vec3(1, 0.7, 1));

    return this -> setTexture(ResourcesPath::asset("textures/fire.tga"));
}

void Fire::update(const gdl::Clock & clock, gdl::Input & input)
{
    if (this -> _steps > 0) {
        switch (this -> getDirection()) {
            case North :
                this -> createFire(glm::vec3(1, 0, 0), North);
                break;

            case South :
                this -> createFire(glm::vec3(-1, 0, 0), South);
                break;

            case East :
                this -> createFire(glm::vec3(0, 0, -1), East);
                break;

            case West :
                this -> createFire(glm::vec3(0, 0, 1), West);
                break;

            case None :    // root of the flames
                this -> createRoot();
                break;
        }
    }
    
    this -> die();
}

void Fire::createFire(glm::vec3 const& position, Direction direction) {
    Fire* obj = new Fire();

    obj->setPosition(this->_position + position);
    obj->setDirection(direction);
    obj->scale(glm::vec3(1, 0.2 * this->getStep(), 1));
    obj->setStep(this->getStep() - 1);

    this->addObject(obj);
}

void Fire::createRoot() {

}
