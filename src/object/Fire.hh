/* 
 * File:   Fire.hh
 * Author: svirch_n
 *
 * Created on 13 June 2014, 14:00
 */

#ifndef FIRE_HH
#define	FIRE_HH

#include "ACube.hh"

class Fire: public ACube{

public:
    
    enum Direction {
        North,
        East,
        South,
        West
    };
    
    Fire(): ACube("fire"), _first(false), _steps(1), _created(false) {}
    Fire(Fire const& obj);
    virtual ~Fire() {}

    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    
    // define the recursiveness number of fire creation.
    // default is 3 (I guess..)
    void setStep(int steps) { this -> _steps = steps; }
    void setDirection(Direction direction) { this->_direction = direction; }
    void setIsFirst(bool first = true) { this->_first = first; }

private:
    
    bool _first;
    int _steps;
    bool _created;
    Direction _direction;

    Direction getDirection() { return this -> _direction; }
    int getStep() { return _steps; }
    int isFirst() { return _first; }
};

#endif	/* FIRE_HH */

