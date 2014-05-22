# include	"AModel.hh"

AModel::AModel(std::string const& modelPath)
	: _animIndex(0)
{

	//Exception if failed ?
	if (_model.load(modelPath) == false)
			std::cout << "Wrong model: " + modelPath << std::endl;
	
	this->scale(glm::vec3(0.005, 0.005, 0.005));
}

void AModel::draw(gdl::AShader & shader, gdl::Clock const& clock)
{
	_model.setCurrentAnim(_animIndex++);
 _model.draw(shader, this->getTransformation(), static_cast<double>(clock.getElapsed()));
}
