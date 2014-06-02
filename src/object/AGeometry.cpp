/*
 * File:   AGeometry.cpp
 * Author: svirch_n
 *
 * Created on 28 May 2014, 16:33
 */

#include "AGeometry.hh"

void AGeometry::draw(gdl::AShader & shader, gdl::Clock const &clock)
{
    (void) clock;
    this->_texture.bind();
    this->_geometry.draw(shader, this->getTransformation(), GL_QUADS);
}
