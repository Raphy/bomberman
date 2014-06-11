/* 
 * File:   Camera.cpp
 * Author: svirch_n
 * 
 * Created on 06 June 2014, 14:31
 */

#include "Camera.hh"

void Camera::update(const gdl::Clock& clock, gdl::Input& input) {
}

void Camera::forceUpdate(gdl::AShader & shader) const {
    this->updateCamera(shader);
}

void Camera::draw(gdl::AShader& shader, const gdl::Clock& clock) {
    if (this->needToMoveCamera())
        this->updateCamera(shader);
}

void Camera::updateCamera(gdl::AShader & shader) const {
    shader.bind();
    shader.setUniform("view", glm::lookAt(this->getPosition(), this->getLookAt(), glm::vec3(0, 1, 0)));
    shader.setUniform("projection", glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f));
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