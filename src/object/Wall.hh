/* 
 * File:   Wall.hh
 * Author: svirch_n
 *
 * Created on 02 June 2014, 16:15
 */

#ifndef WALL_HH
#define	WALL_HH

#include "ACube.hh"

class Wall: public ACube {
public:

    static std::string const Tag;

    Wall(): ACube("wall") {};
    virtual ~Wall();
    virtual void update(gdl::Clock const& clock, gdl::Input& input);
    virtual bool initialize();
};

#endif	/* WALL_HH */

