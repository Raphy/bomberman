#include <cmath>

#include    "AGameObject.hh"

void AGameObject::restoreLastState() {

    _position = _state.position;
    Rectangle const& collider = getCollider();

    double center_x = collider.getX() + collider.getW() / 2;
    double center_y = collider.getY() + collider.getH() / 2;
    
    _position.x = std::floor(center_x);
    _position.z = std::floor(center_y);

}

void AGameObject::saveCurrentState() {
    this->_state.position = this->_position;
}

Rectangle AGameObject::getCollider() const {
    return Rectangle(_position, _scale);
}

void AGameObject::addObject(AGameObject * obj) {
    this->_objects.push_back(obj);
}
