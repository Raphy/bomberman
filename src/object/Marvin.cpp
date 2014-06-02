
#include        "Marvin.hh"

bool Marvin::initialize() {

    this -> _inputs.push_back({SDLK_UP, false, &Marvin::onUpPressed});
    this -> _inputs.push_back({SDLK_DOWN, false, &Marvin::onDownPressed});
    this -> _inputs.push_back({SDLK_LEFT, false, &Marvin::onLeftPressed});
    this -> _inputs.push_back({SDLK_RIGHT, false, &Marvin::onRightPressed});

    this->_animIndex = 0;
    return (true);
}

void Marvin::update(gdl::Clock const &clock,
                    gdl::Input &     input)
{
    for (std::vector<inputStructure>::iterator it = _inputs.begin(); it != _inputs.end(); ++it) {
        
        //Replace getKeyDown which is not implemented yet
        if (input.getKey(it -> value)) {
            if (it -> isPressed == false) {
                it -> isPressed = true;
                this -> _animIndex = 0;
            } else {
                this-> _animIndex++;
            }
            
            // Call the method pointer
            (this->*it -> function)(clock);
            
        } else if (it -> isPressed) { //Replace getKeyUp which is not implemented yet
            it -> isPressed = false;
            this -> _animIndex    = 0;
        }
    }
}

void Marvin::onUpPressed(gdl::Clock const &clock)
{
    translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
    this -> lookNorth();
}

void Marvin::onDownPressed(gdl::Clock const &clock)
{
    translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
    this -> lookSouth();
}

void Marvin::onLeftPressed(gdl::Clock const &clock)
{
    translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    this -> lookWest();
}

void Marvin::onRightPressed(gdl::Clock const &clock)
{
    translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    this -> lookEast();
}


//~ Formatted by Jindent --- http://www.jindent.com
