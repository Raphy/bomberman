/*
 * File:   Box.hh
 * Author: svirch_n
 *
 * Created on 02 June 2014, 19:35
 */

#ifndef BOX_HH
#define BOX_HH

#include    "ACube.hh"

class Box: public ACube
{
    public:
        Box();
        virtual ~Box();


        virtual void onCollision(AGameObject& obj);

        virtual void update(gdl::Clock const &clock, gdl::Input & input);
        virtual bool initialize();
        
        static std::string const Tag;
        
    private:
        
        // call die the next update
        bool _plannedDeath;
};
#endif   /* BOX_HH */