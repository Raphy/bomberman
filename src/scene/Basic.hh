/* 
 * File:   Basic.hh
 * Author: svirch_n
 *
 * Created on 05 June 2014, 16:09
 */

#ifndef BASIC_HH
#define	BASIC_HH

#include "AScene.hh"
#include    "AObject.hh"
#include "SceneArguments.hh"
#include    <vector>

class Basic: public AScene {

private:
    std::vector<AObject*> _objects;
public:
    // A tag which is used to identify the scene. (not necessary but better) 
    static const std::string Tag; 

    // SceneArguments is an hash map key => value (see SceneArguments.hh)
    Basic(): AScene("Basic") {}
    virtual ~Basic() {}

    virtual bool initialize();
    virtual bool update(gdl::Clock const& clock, gdl::Input& input);
    virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);
};
#endif	/* BASIC_HH */

