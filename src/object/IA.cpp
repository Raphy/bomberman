/*
 * File:   AIA.cpp
 * Author: svirch_n
 *
 * Created on 12 June 2014, 14:37
 */

#include <iostream>

#include "API/Manager.hh"
#include "IA.hh"
#include "Lua/Script.hh"

bool IA::initialize()
{
    this -> setSpeed(5);

    this -> pressed = false;

    if (_model.createSubAnim(0, "start", 0, 37) == false) {
        std::cout << "create anim false" << std::endl;
    }

    if (_model.createSubAnim(0, "run", 37, 59) == false) {
        std::cout << "create anim false" << std::endl;
    }

    if (_model.createSubAnim(0, "stop", 75, 130) == false) {
        std::cout << "create anim false" << std::endl;
    }

    this -> scale(glm::vec3(0.0025, 0.0025, 0.0025));


    /*
    ** Dumping the script
    */
    try
      {
	this -> _script = new Lua::Script("./build/ia/default_ia.lua");
	API::Manager::getInstance().registerScript(*this->_script);
	API::Manager::getInstance().registerMe(*this->_script, this);
	
      }
    catch (std::exception& e)
      {
	std::cerr << "[IA] " << "Lua script registering failed" << std::endl;
      }
    if (!this->_script->execute() || !this->_script->initialization())
      {
	std::cerr << "[Lua] " << this->_script->getVirtualMachine().getError() << std::endl;
      }

    return (true);
}

void IA::update(const gdl::Clock & clock, gdl::Input & input)
{
    
//    Debug!
//    
//    if (input.getInput(SDLK_DOWN) && (this -> pressed == false)) {
//        goOneCaseDown();
//        this -> pressed = true;
//    } else if (input.getInput(SDLK_UP) && (this -> pressed == false)) {
//        goOneCaseUp();
//        this -> pressed = true;
//    } else if (input.getInput(SDLK_LEFT) && (this -> pressed == false)) {
//        goOneCaseLeft();
//        this -> pressed = true;
//    } else if (input.getInput(SDLK_RIGHT) && (this -> pressed == false)) {
//        goOneCaseRight();
//        this -> pressed = true;
//    }

    this->saveCurrentState();
    
  if (!this -> _script -> play())
    {
      std::cerr << "[Lua] " << this -> _script -> getVirtualMachine() . getError() << std::endl;
    }

    if (this -> _direction == Down) {
        onDownPressed(clock);
    } else if (this -> _direction == Up) {
        onUpPressed(clock);
    } else if (this -> _direction == Left) {
        onLeftPressed(clock);
    } else if (this -> _direction == Right) {
        onRightPressed(clock);
    }
}

void IA::onCollision(AGameObject& obj) {
    if (obj.getType() == "fire") {
        this->die();
    } else if (obj.getType() == "wall") {
        this->_direction = None;
        this->restoreLastState();
    }
}


void IA::goOneCaseDown()
{
    if (this -> _direction == None) {
        this -> _direction = Down;
        this -> _to        = this -> _position.z - 1;
    }
}

void IA::goOneCaseLeft()
{
    if (this -> _direction == None) {
        this -> _direction = Left;
        this -> _to        = this -> _position.x + 1;
    }
}

void IA::goOneCaseRight()
{
    if (this -> _direction == None) {
        this -> _direction = Right;
        this -> _to        = this -> _position.x - 1;
    }
}

void IA::goOneCaseUp()
{
    if (this -> _direction == None) {
        this -> _direction = Up;
        this -> _to        = this -> _position.z + 1;
    }
}

void IA::onUpPressed(gdl::Clock const &clock)
{
    translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
    this -> lookNorth();

    if (this -> _position.z >= this -> _to) {
        this -> _direction  = None;
        this -> _position.z = this -> _to;
        this -> pressed     = false;
    }

}

void IA::onDownPressed(gdl::Clock const &clock)
{
    translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
    this -> lookSouth();

    if (this -> _position.z <= this -> _to) {
        this -> _direction  = None;
        this -> _position.z = this -> _to;
        this -> pressed     = false;
    }
}

void IA::onLeftPressed(gdl::Clock const &clock)
{
    translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    this -> lookWest();

    if (this -> _position.x >= this -> _to) {
        this -> _direction  = None;
        this -> _position.x = this -> _to;
        this -> pressed     = false;
    }
}

void IA::onRightPressed(gdl::Clock const &clock)
{
    translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    this -> lookEast();
    
    if (this -> _position.x <= this -> _to) {
        this -> _direction  = None;
        this -> _position.x = this -> _to;
        this -> pressed     = false;
    }
}

static const double COLLIDER_SIZE = 0.7;

Rectangle IA::getCollider() const {
    return Rectangle(
        this->_position.x + 0.5 - COLLIDER_SIZE / 2,
        this->_position.z + 0.5 - COLLIDER_SIZE / 2,
        COLLIDER_SIZE,
        COLLIDER_SIZE);
}