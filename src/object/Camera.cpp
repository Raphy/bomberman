/* 
 * File:   Camera.cpp
 * Author: svirch_n
 * 
 * Created on 06 June 2014, 14:31
 */

#include "Camera.hh"
#include "Configuration.hh"

Camera::Camera(AObject const* object) :
  _follow(object), _lookAt(0,0,0), _offset(0, 0, 0)
{
  Configuration::setDefault<float>("fov", 60.2f);
}

void Camera::update(const gdl::Clock& clock, gdl::Input& input) {
}

void Camera::forceUpdate(gdl::AShader & shader, unsigned int cameraNumber) const {
    this->updateCamera(shader, cameraNumber);
}

void Camera::draw(gdl::AShader& shader, const gdl::Clock& clock) {
    if (this->needToMoveCamera())
        this->updateCamera(shader);
}

void Camera::updateCamera(gdl::AShader & shader, unsigned int cameraNumber) const {
    
    if (cameraNumber == 0)
        cameraNumber = 1;
    
    shader.bind();
    shader.setUniform("view", glm::lookAt(this->getPosition(), this->getLookAt(), glm::vec3(0, 1, 0)));
    shader.setUniform("projection", glm::perspective(Configuration::get<float>("fov"), (800.0f / cameraNumber) / 600.0f, 0.1f, 200.0f));
}


bool Camera::needToMoveCamera() const {
    if (this->_follow == nullptr)
        return false;
    return true;
    return this->_lastPosition != this->_follow->getPosition();
    
}

glm::vec3 Camera::getLookAt() const {
    if (this->_follow != nullptr)
        return this->_follow->getPosition();
    return this->_lookAt;
}

glm::vec3 Camera::getPosition() const {
    if (this->_follow != nullptr)
        return this->_follow->getPosition() + this->_offset;
    return this->_position;
}

void Camera::zoom(double diff) {
    this->_offset.y -= diff;
    this->_offset.z += diff;
}

void Camera::zoomPlus() {
    zoom(0.2);
}
void Camera::zoomMinus() {
    zoom(-0.2);
}
