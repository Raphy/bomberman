#include    "AGameObject.hh"


void AGameObject::restoreLastState() {
    this->_position = this->_state.position;
    this->_rotation = this->_state.rotation;
    this->_scale = this->_state.scale;
}

void AGameObject::saveCurrentState() {
    this->_state.position = this->_position;
    this->_state.rotation = this->_rotation;
    this->_state.scale = this->_scale;
}
