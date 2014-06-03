/*
 * File:   AGeometry.hh
 * Author: svirch_n
 *
 * Created on 28 May 2014, 16:33
 */

#ifndef AGEOMETRY_HH
#define AGEOMETRY_HH

#include "AGameObject.hh"

class AGeometry:
    public AGameObject
{
    public:
        AGeometry() {};
        virtual ~AGeometry() {};
        bool setTexture(std::string const &path) { return _texture.load(path);}
        virtual void draw(gdl::AShader & shader, gdl::Clock const &clock);

    protected:
        gdl::Texture  _texture;
        gdl::Geometry _geometry;
};
#endif   /* AGEOMETRY_HH */


//~ Formatted by Jindent --- http://www.jindent.com
