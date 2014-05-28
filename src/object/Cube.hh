/*
 * File:   Cube.hh
 * Author: svirch_n
 *
 * Created on 28 May 2014, 18:00
 */

#ifndef CUBE_HH
#define CUBE_HH

#include "AGeometry.hh"

class Cube: public AGeometry
{
    public:
        Cube();
        virtual ~Cube(){};
        virtual bool initialize() { return true; }

        
    private:
        virtual void update(gdl::Clock const &clock,
                            gdl::Input &     input);
};
#endif   /* CUBE_HH */


//~ Formatted by Jindent --- http://www.jindent.com
