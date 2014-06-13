/* 
 * File:   Bomb.cpp
 * Author: svirch_n
 * 
 * Created on 03 June 2014, 13:41
 */

#include "Bomb.hh"

std::string const Bomb::Tag = "bomb";

static const double BOMBTIME = 2;

void Bomb::update(const gdl::Clock& clock, gdl::Input& input) {

    this->_time += clock.getElapsed();
    
    if (this -> _time >= BOMBTIME) {
        std::cout << "BOOM" << std::endl;
        this -> die();
        this -> createFire();
    }
}

void Bomb::createFire() {
    
    // TO DO
}