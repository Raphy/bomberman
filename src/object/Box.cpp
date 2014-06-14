/* 
 * File:   Box.cpp
 * Author: svirch_n
 * 
 * Created on 02 June 2014, 19:35
 */

#include <cstdlib>

#include "BombRangeBuff.hh"
#include "Box.hh"
#include "ResourcesPath.hh"
#include "SpeedBuff.hh"

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
      {
	/*if (rand() % 10 == 0)
	  {*/
	    AGameObject* buff;
	    switch(rand() % 2)
	      {
	      case 0:
		{
		  buff = new SpeedBuff();
		  break;
		}
	      case 1:
		{
		  buff = new BombRangeBuff();
		  break;
		}
	      }
	    buff->setPosition(glm::vec3(static_cast<int>(this->_position.x),
					static_cast<int>(this->_position.y),
					static_cast<int>(this->_position.z)));
	    buff->initialize();
	    this->addObject(buff);
	    std::cout << "Buff: " << buff->getType() << std::endl;
	    /*}*/
	    this->die();
      }
    else if (obj.getType() == "wall")
        this->restoreLastState();
}
