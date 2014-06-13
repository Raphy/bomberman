/* 
 * File:   Fire.cpp
 * Author: svirch_n
 * 
 * Created on 13 June 2014, 14:00
 */

#include "Fire.hh"
#include "ResourcesPath.hh"

bool Fire::initialize() {
    
    this -> scale(glm::vec3(0.8, 0.7, 0.8));
    
    return this -> setTexture(ResourcesPath::asset("textures/fire.tga"));
}

void Fire::update(const gdl::Clock& clock, gdl::Input& input) {

    if (this->_created == false && this->_steps > 0) {

    std::list<glm::vec3> fires;
    
    glm::vec3 position = glm::vec3(static_cast<int>(this->_position.x), static_cast<int>(this->_position.y), static_cast<int>(this->_position.z));
    
    if (this->_first) {
        switch (this->getDirection()) {
            case North:
                fires.push_back(position + glm::vec3(0, 0, 0));
                break;
            case South:
                fires.push_back(position + glm::vec3(0, 0, 0));
                break;
            case East:
                fires.push_back(position + glm::vec3(0, 0, 0));
                break;
            case West:
                fires.push_back(position + glm::vec3(0, 0, 0));
                break;
        }
    } else {
        fires.push_back(position + glm::vec3(0, 0, 1));
        fires.push_back(position + glm::vec3(0, 0, -1));
        fires.push_back(position + glm::vec3(1, 0, 0));
        fires.push_back(position + glm::vec3(-1, 0, 0));
    }

    for (auto it = fires.begin(); it != fires.end(); ++it) {
        Fire * fire = new Fire();
        fire->setPosition(*it);
        this->addObject(fire);
    }
    }
    this->_created = true;
    
    
}