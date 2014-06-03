# include	"AModel.hh"

AModel::AModel(std::string const& modelPath, std::string const& id): AGameObject(id)
{
    
    //Exception if failed ?
    if (_model.load(modelPath) == false)
        std::cout << "Wrong model: " + modelPath << std::endl;
}

void AModel::draw(gdl::AShader & shader, gdl::Clock const& clock)
{
    _model.draw(shader, this->getTransformation(), static_cast<double>(clock.getElapsed()));
}
