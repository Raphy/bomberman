/*
 * File:   Fire.cpp
 * Author: svirch_n
 *
 * Created on 13 June 2014, 14:00
 */

#include "Fire.hh"
#include "ResourcesPath.hh"

Fire::Fire() : ACube("fire"), _steps(0), _direction(None), _created(false), _time(0.5) {
}

bool Fire::initialize()
{
    this -> scale(glm::vec3(1, 0.2, 1));

    return this -> setTexture(ResourcesPath::asset("textures/fire.tga"));
}

void Fire::update(const gdl::Clock & clock, gdl::Input & input)
{
    if (this -> _created == false && _steps > 0) {
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
        this->_created = true;
    }
    
    this->_time -= clock.getElapsed();
    if (this->_time <= 0)
        this->die();
}

void Fire::createFire(glm::vec3 const& position, Direction direction) {
    Fire* obj = new Fire();

    obj->setPosition(this->_position + position);
    obj->setDirection(direction);
    obj->scale(glm::vec3(1, 1, 1));
    obj->setStep(this->getStep() - 1);
    obj->setParent(getParent());

    this->addObject(obj);
}

void Fire::onCollision(AGameObject& other) {
    if ((other.getType() == "wall"
         || other.getType() == "box")
         && other.getPosition() == this->getPosition()) {
        this->die();
    }
}


void Fire::createRoot() {
    this -> createFire(glm::vec3(1, 0, 0), North);
    this -> createFire(glm::vec3(-1, 0, 0), South);
    this -> createFire(glm::vec3(0, 0, -1), East);
    this -> createFire(glm::vec3(0, 0, 1), West);
}
