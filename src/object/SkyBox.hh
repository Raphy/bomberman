/* 
 * File:   SkyBox.hh
 * Author: svirch_n
 *
 * Created on 14 June 2014, 20:53
 */

#ifndef SKYBOX_HH
#define	SKYBOX_HH

#include "ACube.hh"

class SkyBox: public ACube {

public:
    
    static std::string const Tag;
    
    SkyBox(): ACube("skybox") {}
    virtual ~SkyBox() {}
    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input) {}

};

#endif	/* SKYBOX_HH */

