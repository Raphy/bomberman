#include <iostream>
#include "AWidget.hh"

AWidget::AWidget(const std::string& path, const glm::vec3& position, const glm::vec3& scale, int cur)
  : _texturePath(path), _position(position), _scale(scale), _cur(cur)
{

}

AWidget::~AWidget()
{

}

bool AWidget::initialize()
{
  if (_texture.load(_texturePath) == false)
    {
      std::cerr << "Cannot load the widget texture" << std::endl;
      return false;
    }

  _geometry.setColor(glm::vec4(1, 1, 1, 1));

  _geometry.pushVertex(glm::vec3(0, 0, 0));
  _geometry.pushVertex(glm::vec3(1, 0, 0));
  _geometry.pushVertex(glm::vec3(1, 1, 0));
  _geometry.pushVertex(glm::vec3(0, 1, 0));

  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));

  _geometry.build();

  return true;
}

void AWidget::update(gdl::Clock const& clock, gdl::Input& input)
{

}

void AWidget::draw(gdl::AShader & shader, gdl::Clock const& clock)
{
  (void)clock;

  glm::mat4 transform(1);

  transform = glm::translate(transform, _position);
  transform = glm::scale(transform, _scale);

  _texture.bind();

  _geometry.draw(shader, transform, GL_QUADS);
}

int AWidget::getCur() const
{
  return _cur;
}

glm::vec3 AWidget::getPos() const
{
  return _position;
}
