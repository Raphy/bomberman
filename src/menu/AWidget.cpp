#include "AWidget.hh"


AWidget::AWidget(bool cursor, const std::string& path, glm::vec3 position, glm::vec3 scale)
{
  _cursor = cursor;
  _texturePath = path;
  _position = position;
  _scale = scale;
}

AWidget::~AWidget()
{
}

bool AWidget::initialize()
{
  _cursor = false;

  if (_texture.load(_texturePath) == false)
    {
      std::cerr << "Cannot load the wall texture" << std::endl;
      return false;
    }
  /*
  _geometry.setColor(glm::vec4(1, 1, 1, 1));

  _geometry.pushVertex(glm::vec3(0, 0, 0));
  _geometry.pushVertex(glm::vec3(0, 0, 0));
  _geometry.pushVertex(glm::vec3(0, 0, 0));
  _geometry.pushVertex(glm::vec3(0, 0, 0));

  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));

  _geometry.build();
  */
}

void AWidget::update(gdl::Clock const& clock, gdl::Input& input)
{

}

void AWidget::draw(gdl::AShader & shader, gdl::Clock const& clock)
{

}
