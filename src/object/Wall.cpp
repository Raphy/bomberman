/* 
 * File:   Wall.cpp
 * Author: svirch_n
 * 
 * Created on 02 June 2014, 16:15
 */

#include "Wall.hh"

Wall::Wall() {
    
    this->setTexture("./build/assets/textures/wall.tga");
    
}

Wall::Wall(const Wall& orig) {
}

Wall::~Wall() {
}

