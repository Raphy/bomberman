/*
 * File:   AGeometry.hh
 * Author: svirch_n
 *
 * Created on 28 May 2014, 16:33
 */

#ifndef AGEOMETRY_HH
#define AGEOMETRY_HH

#include "AGameObject.hh"

class AGeometry: public AGameObject
{
    public:
        
        virtual ~AGeometry() {};
        bool setTexture(std::string const &path) { return _texture.load(path); }
        
        void drawTexture();
        void drawGeometry(gdl::AShader & shader, gdl::Clock const &clock);
        void draw(gdl::AShader & shader, gdl::Clock const &clock);
        
    protected:
        AGeometry(std::string const& id): AGameObject(id) {};
        gdl::Texture  _texture;
        gdl::Geometry _geometry;
};
#endif   /* AGEOMETRY_HH */


//~ Formatted by Jindent --- http://www.jindent.com
