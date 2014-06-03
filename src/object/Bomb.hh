/* 
 * File:   Bomb.hh
 * Author: svirch_n
 *
 * Created on 03 June 2014, 13:41
 */

#ifndef BOMB_HH
#define	BOMB_HH

#include    "AModel.hh"

class Bomb: public AModel {

    public:
    Bomb(): AModel("./build/assets/bomb.fbx", "bomb") { setPosition(glm::vec3(0, 0, 0)); setSpeed(10); scale(glm::vec3(0.02, 0.02, 0.02)); }
    virtual ~Bomb() {}
    virtual bool initialize() { return true; };
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    
    static std::string const Tag;

};

#endif	/* BOMB_HH */

