
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
                (this->*it -> functionPressed)(clock);
            }
            
            // Call the method pointer
            (this->*it -> function)(clock);
            
        } else if (it -> isPressed) { //Replace getKeyUp which is not implemented yet
            it -> isPressed = false;
            (this->*it -> functionReleased)(clock);
        }
    }
    
}

void Marvin::stop(const gdl::Clock&) {
    this->totalPressed--;
    if (this->totalPressed == 0)
        _model.setCurrentSubAnim("stop", false);
}


void Marvin::run(const gdl::Clock&) {
    this->totalPressed++;
    _model.setCurrentSubAnim("run");
}


void Marvin::none(gdl::Clock const &clock) {
    (void) clock;
}

void Marvin::setBindKeys(const inputBinding& bind) {
    this -> _inputs.clear();
    
    // Key, pressed status, onKey, onPressed, OnReleased
    this -> _inputs.push_back({bind.up, false, &Marvin::onUpPressed, &Marvin::run, &Marvin::stop});
    this -> _inputs.push_back({bind.down, false, &Marvin::onDownPressed, &Marvin::run, &Marvin::stop});
    this -> _inputs.push_back({bind.left, false, &Marvin::onLeftPressed, &Marvin::run, &Marvin::stop});
    this -> _inputs.push_back({bind.right, false, &Marvin::onRightPressed, &Marvin::run, &Marvin::stop});
    this -> _inputs.push_back({bind.bomb, false, &Marvin::none, &Marvin::onBombPressed, &Marvin::none});
}

void Marvin::onCollision(AGameObject& obj) {
    
    if (obj.getType() == "fire") {
        this->die();
    } else if (obj.getType() == "wall"
            || obj.getType() == "box") {
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

static const double COLLIDER_SIZE = 0.8;

void Marvin::onBombPressed(const gdl::Clock& clock) {
    AGameObject* bomb = new Bomb();
    
     bomb->setPosition(glm::vec3(static_cast<int>(this->_position.x + 0.5),
                                0,
                                static_cast<int>(this->_position.z + 0.5)));
    this->addObject(bomb);
}


Rectangle Marvin::getCollider() const {
    return Rectangle(
        this->_position.x + 0.5 - COLLIDER_SIZE / 2,
        this->_position.z + 0.5 - COLLIDER_SIZE / 2,
        COLLIDER_SIZE,
        COLLIDER_SIZE);
}
//~ Formatted by Jindent --- http://www.jindent.com
