/*
 * File:   Box.hh
 * Author: svirch_n
 *
 * Created on 02 June 2014, 19:35
 */

#ifndef BOX_HH
#define BOX_HH

#include    "Cube.hh"

class Box: public Cube
{
    public:
        Box();
        virtual ~Box();

        virtual void update(gdl::Clock const &clock, gdl::Input & input);
        virtual bool initialize();;
};
#endif   /* BOX_HH */