
#include        "Marvin.hh"
#include "Bomb.hh"

std::string const Marvin::Tag = "marvin";

bool Marvin::initialize() {

    this->setSpeed(5);
    
    if (_model.createSubAnim(0, "start", 0, 37) == false
            || _model.createSubAnim(0, "run", 37, 59) == false
            || _model.createSubAnim(0, "stop", 75, 130) == false) {
       
        std::cout << "create anim false" << std::endl;
        return false;
    
    }

    this->scale(glm::vec3(0.0025, 0.0025, 0.0025));
    
    return (true);
}

void Marvin::update(gdl::Clock const &clock,
                    gdl::Input &     input)
{
    this->saveCurrentState();
    
    for (std::vector<inputStructure>::iterator it = _inputs.begin(); it != _inputs.end(); ++it) {
        
        //Replace getKeyDown which is not implemented yet
        if (input.getKey(it -> value)) {
            if (it -> isPressed == false) {
                it -> isPressed = true;
                this->totalPressed++;
                _model.setCurrentSubAnim("run");
                
            }
            
            // Call the method pointer
            (this->*it -> function)(clock);
            
        } else if (it -> isPressed) { //Replace getKeyUp which is not implemented yet
            it -> isPressed = false;
            this->totalPressed--;
            if (this->totalPressed == 0)
            _model.setCurrentSubAnim("stop", false);
        }
    }
    
}

void Marvin::setBindKeys(const inputBinding& bind) {
    this -> _inputs.clear();
    
    this -> _inputs.push_back({bind.up, false, &Marvin::onUpPressed});
    this -> _inputs.push_back({bind.down, false, &Marvin::onDownPressed});
    this -> _inputs.push_back({bind.left, false, &Marvin::onLeftPressed});
    this -> _inputs.push_back({bind.right, false, &Marvin::onRightPressed});
    this -> _inputs.push_back({bind.bomb, false, &Marvin::onBombPressed});
}

void Marvin::onCollision(AGameObject& obj) {
    
    if (obj.getType() == "wall") {
        this->restoreLastState();
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

void Marvin::onBombPressed(const gdl::Clock& clock) {
    AGameObject* bomb = new Bomb();
    
    bomb->setPosition(glm::vec3(static_cast<int>(this->_position.x),
                                static_cast<int>(this->_position.y),
                                static_cast<int>(this->_position.z)));
    this->addObject(bomb);
}

static const double COLLIDER_SIZE = 0.7;

Rectangle Marvin::getCollider() const {
    return Rectangle(
        this->_position.x + 0.5 - COLLIDER_SIZE / 2,
        this->_position.z + 0.5 - COLLIDER_SIZE / 2,
        COLLIDER_SIZE,
        COLLIDER_SIZE);
}
//~ Formatted by Jindent --- http://www.jindent.com
