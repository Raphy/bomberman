
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
        std::cout << "owned by " << obj.getParent() << std::endl;
        this->die();
    } else if (obj.getType() == "wall"
            || obj.getType() == "box") {
        this->restoreLastState(obj);
    }
}

void Marvin::onBombPressed(const gdl::Clock& clock) {
    putBomb();
}