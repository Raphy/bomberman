/* 
 * File:   Bomb.hh
 * Author: svirch_n
 *
 * Created on 03 June 2014, 13:41
 */

#ifndef BOMB_HH
#define	BOMB_HH

#include    "AModel.hh"
#include    "ResourcesPath.hh"
#include "APlayer.hh"

class Bomb: public AModel {

public:
    Bomb(): AModel(ResourcesPath::asset("bomb.fbx"), "bomb"), _time(0) { setPosition(glm::vec3(0, 0, 0)); setSpeed(0); scale(glm::vec3(0.02, 0.02, 0.02)); }
    virtual ~Bomb() {}
    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    virtual double getTime() const { return this->_time; }
    
    void setParentObject(APlayer *parent) { this->_parentObject = parent; }
    void setSteps(int value) { this->_steps = value; }
    int getSteps() const { return this->_steps; }
    
    static std::string const Tag;
   
protected:
    double      _time;
    int         _steps;
    APlayer *   _parentObject;
    
    void createFire();
};

#endif	/* BOMB_HH */

