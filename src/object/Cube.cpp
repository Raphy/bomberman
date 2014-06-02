/* 
 * File:   Cube.cpp
 * Author: svirch_n
 * 
 * Created on 28 May 2014, 18:00
 */

#include "Cube.hh"

Cube::Cube() {
    
    this->setTexture("./build/assets/textures/blank.tga");
    
    _geometry.setColor(glm::vec4(1, 0, 0, 1));

    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));

    
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));

    _geometry.setColor(glm::vec4(1, 1, 1, 1));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
    
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.setColor(glm::vec4(1, 1, 1, 1));
    
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
    
    
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    
    _geometry.setColor(glm::vec4(1, 1, 1, 1));
    
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
    
    
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    
    _geometry.setColor(glm::vec4(1, 1, 1, 1));
    
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
    
    
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    
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

void Cube::update(gdl::Clock const &clock, gdl::Input &input)
{
    if (input.getKey(SDLK_UP))
        translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_DOWN))
        translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_LEFT))
        translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_RIGHT))
        translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
}

