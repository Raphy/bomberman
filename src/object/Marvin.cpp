
#include        "Marvin.hh"

bool Marvin::initialize()
{
    this -> _inputs.emplace(SDLK_UP, &Marvin::onUpPressed);
    this -> _inputs.emplace(SDLK_DOWN, &Marvin::onDownPressed);
    this -> _inputs.emplace(SDLK_LEFT, &Marvin::onLeftPressed);
    this -> _inputs.emplace(SDLK_RIGHT, &Marvin::onRightPressed);
    
    return (true);
}

void Marvin::update(gdl::Clock const &clock,
        gdl::Input &     input)
{
    for (std::map<int, inputFunction>::iterator it = _inputs.begin(); it != _inputs.end(); ++it) {
        if (input.getKey(it -> first)) {
            (this->*it -> second)(clock);
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
