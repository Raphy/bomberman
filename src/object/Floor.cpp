/* 
 * File:   Floor.cpp
 * Author: svirch_n
 * 
 * Created on 14 June 2014, 23:18
 */

#include "ResourcesPath.hh"
#include "Floor.hh"

std::string const Floor::Tag = "floor";

Floor::Floor() : AGeometry("floor") {
    
    _geometry.setColor(glm::vec4(1, 1, 1, 1));
    
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
    
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    
    _geometry.build();
}

bool Floor::initialize() {
    return setTexture(ResourcesPath::asset("textures/wall.tga"));
}

void Floor::update(const gdl::Clock& clock, gdl::Input& input) {

}
