/* 
 * File:   AGeometry.hh
 * Author: svirch_n
 *
 * Created on 28 May 2014, 16:33
 */

#ifndef AGEOMETRY_HH
#define	AGEOMETRY_HH

#include "AGameObject.hh"

class AGeometry: public AGameObject {
public:
    AGeometry();
    virtual ~AGeometry();
private:
    virtual void draw(gdl::AShader & shader, gdl::Clock const& clock);
};

#endif	/* AGEOMETRY_HH */

