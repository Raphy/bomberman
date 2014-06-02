/* 
 * File:   Wall.hh
 * Author: svirch_n
 *
 * Created on 02 June 2014, 16:15
 */

#ifndef WALL_HH
#define	WALL_HH

#include "Cube.hh"

class Wall: public Cube {
public:
    Wall();
    Wall(const Wall& orig);
    virtual ~Wall();
private:

};

#endif	/* WALL_HH */

