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

std::string const IA::Tag = "ia";
IA::IA() : APlayer(ResourcesPath::asset("marvin_ia.fbx"), Tag), _direction(None), pressed(false) {
    this->start();
}

IA::~IA()
{
//   this->join();
  //delete this->_script;
}

bool IA::initAnim() {
    return true;
}

bool IA::initialize()
{
    if (APlayer::initialize() == false)
        return false;
    
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
    {
        ScopedLock lk(this->_mutex);
       this->_clock = clock;
    }
    this->_cv->signal();
    {
        ScopedLock lk(this->_mutex);
        this->saveCurrentState();
    }    
}

void * IA::routine()
{
    std::cout << "I'm a little thread !!!" << std::endl;
    while (this->_status == ALIVE)
    {
        this->_cv->wait();
        std::cout << "I'm a thread !!!" << std::endl;
        if (!this -> _script -> play())
        {
          std::cerr << "[Lua] " << this -> _script -> getVirtualMachine() . getError() << std::endl;
        }
    
        {
            ScopedLock lk(this->_mutex);
            if (this -> _direction == Down) {
                this -> onDownPressed(this -> _clock);
            } else if (this -> _direction == Up) {
                this -> onUpPressed(this -> _clock);
            } else if (this -> _direction == Left) {
                this -> onLeftPressed(this -> _clock);
            } else if (this -> _direction == Right) {
                this -> onRightPressed(this -> _clock);
            }
        }
    }
    return nullptr;
}

void IA::onCollision(AGameObject& obj) {
    if (obj.getType() == "fire") {
        std::cout << "owned by " << obj.getParent() << std::endl;
        this->die();
    } else if (obj.getType() == "wall"
            || obj.getType() == "box") {
        this->_direction = None;
        this->restoreLastState(obj);
    }
}


void IA::goOneCaseDown()
{
    if (this -> _direction == None) {
        this -> _direction = Down;
        this -> _to        = this -> _position.z - 1;
        this->run();
    }
}

void IA::goOneCaseLeft()
{
    if (this -> _direction == None) {
        this -> _direction = Left;
        this -> _to        = this -> _position.x + 1;
        this->run();
    }
}

void IA::goOneCaseRight()
{
    if (this -> _direction == None) {
        this -> _direction = Right;
        this -> _to        = this -> _position.x - 1;
        this->run();
    }
}

void IA::goOneCaseUp()
{
    if (this -> _direction == None) {
        this -> _direction = Up;
        this -> _to        = this -> _position.z + 1;
        this->run();
    }
}

void IA::stopMouvement(float& to) {
    this -> _direction  = None;
    to                  = this -> _to;
    this -> pressed     = false;
    this->stop();
}

void IA::onUpPressed(gdl::Clock const &clock)
{
    APlayer::onUpPressed(clock);

    if (this -> _position.z >= this -> _to) {
        this->stopMouvement(this->_position.z);
    }

}

void IA::onDownPressed(gdl::Clock const &clock)
{
    APlayer::onDownPressed(clock);

    if (this -> _position.z <= this -> _to) {
        this->stopMouvement(this->_position.z);
    }
}

void IA::onLeftPressed(gdl::Clock const &clock)
{
    APlayer::onLeftPressed(clock);
    
    if (this -> _position.x >= this -> _to) {
        this->stopMouvement(this->_position.x);
    }
}

void IA::onRightPressed(gdl::Clock const &clock)
{
    APlayer::onRightPressed(clock);
    
    if (this -> _position.x <= this -> _to) {
        this->stopMouvement(this->_position.x);
    }
}
