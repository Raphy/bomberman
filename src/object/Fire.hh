/* 
 * File:   Fire.hh
 * Author: svirch_n
 *
 * Created on 13 June 2014, 14:00
 */

#ifndef FIRE_HH
#define	FIRE_HH

#include "ACube.hh"

class Fire: public ACube {

public:

    static std::string const Tag;
    
    enum Direction {
        North,
        East,
        South,
        West,
        None //the first one is None
    };
    
    Fire();
    virtual ~Fire() {}

    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    
    // define the recursiveness number of fire creation.
    // default is 3 (I guess..)
    void setStep(int steps) { this -> _steps = steps; }
    void setDirection(Direction direction) { this->_direction = direction; }

    virtual void onCollision(AGameObject&);

private:
    
    int         _steps;
    Direction   _direction;
    bool        _created;
    double      _time;

    Direction   getDirection() const { return this -> _direction; }
    void        setTime(double time) { this->_time = time; }
    double      getTime() const { return this->_time; }
    
    int getStep() const { return _steps; }
    int isFirst() const { return _direction == None; }
    
    void createFire(glm::vec3 const&, Direction);
    void createRoot();
};

#endif	/* FIRE_HH */

