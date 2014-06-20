/* 
 * File:   Demo.hh
 * Author: svirch_n
 *
 * Created on 15 June 2014, 21:25
 */

#ifndef DEMO_HH
#define	DEMO_HH

#include "AScene.hh"
#include "AGameObject.hh"
#include <list>


class Demo : public AScene {

public:
    
    Demo(const SceneArguments& scene);
    virtual ~Demo() {}

    virtual bool initialize();
    virtual bool update(const gdl::Clock& clock, gdl::Input& input);
    virtual bool draw(gdl::AShader& shader, const gdl::Clock& clock);

private:
    SceneArguments& _arg;
    std::list<AGameObject*>     _objects;
};

#endif	/* DEMO_HH */

