#include "AWidget.hh"

#include <iostream>

/*
  Penser a add le Son Menu + add dans le widget le son !!
*/

AWidget::AWidget(const std::string& path, glm::vec3 position, glm::vec3 scale)
{
  _texturePath = path;
  _position = position;
  _scale = scale;
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

/* faire le switch like DEFINE SNAKE*/
void AWidget::update(gdl::Clock const& clock, gdl::Input& input)
{
  /*
  if (input.getKey(SDLK_UP))
    std::cout << "UP : " <<  _cursor << std::endl;
  if (input.getKey(SDLK_DOWN))
    std::cout << "DOWN" << std::endl;
  if (input.getKey(SDLK_SPACE))
    std::cout << "SPACE" << std::endl;
  */
}

void AWidget::draw(gdl::AShader & shader, gdl::Clock const& clock)
{
  (void)clock;

  shader.bind();

  glm::mat4 transform(1);

  transform = glm::translate(transform, _position);
  transform = glm::scale(transform, _scale);

  _texture.bind();

  _geometry.draw(shader, transform, GL_QUADS);
}