/* 
 * File:   Floor.hh
 * Author: svirch_n
 *
 * Created on 14 June 2014, 23:18
 */

#ifndef FLOOR_HH
#define	FLOOR_HH

#include "AGeometry.hh"


class Floor: public AGeometry {
public:
    Floor();
    virtual ~Floor() {}

    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input);


    static std::string const Tag;
};

#endif	/* FLOOR_HH */

