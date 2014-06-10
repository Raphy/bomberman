/*
 * File:   Basic.cpp
 * Author: svirch_n
 *
 * Created on 05 June 2014, 16:09
 */

#include "Basic.hh"
#include "Marvin.hh"
#include    "Box.hh"
#include    "Wall.hh"
#include "Camera.hh"
#include    <vector>

bool Basic::initialize()
{
    AObject * obj;
    Camera *  camera;

    for (int j = -8; j <= 8; j += 2) {
        for (int i = -8; i <= 8; i += 2) {
            obj = new Wall();
            obj -> initialize();
            obj -> isStatic();
            obj -> setPosition(glm::vec3(i, 0.5, j));
            this -> _objects.push_back(obj);
        }
    }

    for (int i = -10; i <= 10; i++) {
        obj = new Wall();
        
        obj -> initialize();
        obj -> isStatic();
        obj -> setPosition(glm::vec3(i, 0.5, -10));
            
        this -> _objects.push_back(obj);
    }

    for (int i = -10; i <= 10; i++) {
        obj = new Wall();
        obj -> initialize();
        obj->isStatic();
        obj -> setPosition(glm::vec3(i, 0.5, 10));
            
        this -> _objects.push_back(obj);
    }

    for (int i = -10; i <= 10; i++) {
        obj = new Wall();
        obj -> initialize();
        obj->isStatic();
        obj -> setPosition(glm::vec3(10, 0.5, i));
            
        this -> _objects.push_back(obj);
    }

    for (int i = -10; i <= 10; i++) {
        obj = new Wall();
        obj -> initialize();
        obj->isStatic();
        obj -> setPosition(glm::vec3(-10, 0.5, i));
            
        this -> _objects.push_back(obj);
    }

    obj = new Marvin();
    obj -> initialize();
    this -> _objects.push_back(obj);  
    
    camera = new Camera(obj);    
    camera -> setOffset(glm::vec3(0, 10, -10));
    camera -> initialize();
    this -> _objects.push_back(camera);
    
    this->addCamera("principal", camera);
    
    return true;
}

bool Basic::update(const gdl::Clock & clock, gdl::Input & input)
{
    std::vector<AObject *>::iterator it = this -> _objects.begin();

    while (it != this -> _objects.end()) {
        (*it) -> update(clock, input);
        ++it;
    }

    return true;
}

bool Basic::draw(gdl::AShader & shader, const gdl::Clock & clock)
{
    std::vector<AObject *>::iterator it = this -> _objects.begin();
    
    while (it != this -> _objects.end()) {
        (*it) -> draw(shader, clock);
        ++it;
    }

    it = this -> _objects.begin();

    return true;
}


//~ Formatted by Jindent --- http://www.jindent.com
