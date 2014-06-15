#include <cmath>

#include    "AGameObject.hh"

void AGameObject::restoreLastState(AGameObject const& obj) {

    _position = _state.position;
    Rectangle const& collider = getCollider();
        
    if (std::floor(std::get<0>(obj.getPosition()) + 0.5) == std::floor(this->_position.x + 0.5)) {
        double center_x = collider.getX() + collider.getW() / 2;
        _position.x = std::floor(center_x);
    }
    
    
    if (std::floor(std::get<1>(obj.getPosition()) + 0.5) == std::floor(this->_position.z + 0.5)) {
        double center_y = collider.getY() + collider.getH() / 2;
        _position.z = std::floor(center_y);
    }

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
