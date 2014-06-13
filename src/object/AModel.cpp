# include	"AModel.hh"
# include       "Exception.hh"

AModel::AModel(std::string const& modelPath, std::string const& id): AGameObject(id)
{

    //Exception if failed ?
    if (_model.load(modelPath) == false)
        throw Exception("Could not load '" + modelPath + "'");
}

void AModel::draw(gdl::AShader & shader, gdl::Clock const& clock)
{
    _model.draw(shader, this->getTransformation(), static_cast<double>(clock.getElapsed()));
}
