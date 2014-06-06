
#include "AObject.hh"


glm::mat4 AObject::getTransformation()
{
    if (this->_static)
        return this->_transformation;
    
    glm::mat4 transform(1);

    /*
     * With a matrix transform the first calcul is applied at the end
     * In this case the transformation is scale, rotation and translation
     */
    
    transform = glm::translate(transform, _position);
    
    transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
    
    transform = glm::scale(transform, _scale);

    return (transform);
}

void AObject::setPosition(glm::vec3 position) {
    _position = position;
    this->checkStaticObject();
}


void AObject::lookAt(const glm::vec3& point) {
    _rotation = point;
    this->checkStaticObject();
}

void AObject::lookEast() {
    this -> lookAt(glm::vec3(0, -90, 0));
    this->checkStaticObject();
}

void AObject::lookNorth() {
    this -> lookAt(glm::vec3(0, 0, 0));
    this->checkStaticObject();
}

void AObject::lookSouth() {
    this -> lookAt(glm::vec3(0, 180, 0));
    this->checkStaticObject();
}

void AObject::lookWest() {
    this -> lookAt(glm::vec3(0, 90, 0));
    this->checkStaticObject();
}

void AObject::rotate(const glm::vec3& axis, float angle) {
    _rotation += axis * angle;
    this->checkStaticObject();
}

void AObject::translate(const glm::vec3& v) {
    _position += v;
    this->checkStaticObject();
}

void AObject::scale(const glm::vec3& scale) {
    _scale *= scale;
    this->checkStaticObject();
}

void AObject::checkStaticObject() {
    if (this->_static)
        this->_transformation = this->getTransformation();
}



//~ Formatted by Jindent --- http://www.jindent.com
