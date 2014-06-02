# include	"AModel.hh"

AModel::AModel(std::string const& modelPath)
: _animIndex(0)
{
    
    //Exception if failed ?
    if (_model.load(modelPath) == false)
        std::cout << "Wrong model: " + modelPath << std::endl;
    
    if (_model.createSubAnim(0, "start", 0, 37) == false)
       std::cout << "create anim false" << std::endl;

    if (_model.createSubAnim(0, "run", 37, 59) == false)
       std::cout << "create anim false" << std::endl;

    if (_model.createSubAnim(0, "stop", 59, 120) == false)
       std::cout << "create anim false" << std::endl;

    
    if (_model.setCurrentSubAnim("run") == false)
        std::cout << "set anim false" << std::endl;

//    _model.setCurrentAnim(0);
    
    this->scale(glm::vec3(0.005, 0.005, 0.005));
}

void AModel::draw(gdl::AShader & shader, gdl::Clock const& clock)
{
    _model.draw(shader, this->getTransformation(), static_cast<double>(clock.getElapsed()));
}
