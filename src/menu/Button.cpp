#include "Button.hh"

Button::Button(bool cursor, const std::string& path, glm::vec3 pos, glm::vec3 scale)
  : AWidget(path, pos, scale), _cursor(cursor)
{
  glm::vec3 tmp(-30,0,0);

  c = new AWidget("./build/assets/img/bombe.tga", pos + tmp, glm::vec3(20, 20, 0));
}

Button::~Button()
{
}

bool Button::initialize()
{
  c->initialize();
  return  AWidget::initialize();
}

void Button::update(gdl::Clock const& clock, gdl::Input& input)
{
  if (input.getKey(SDLK_UP))
    std::cout << "UP : "  << std::endl;
  if (input.getKey(SDLK_DOWN))
    std::cout << "DOWN" << std::endl;
  if (input.getKey(SDLK_SPACE))
    std::cout << "SPACE" << std::endl;
}

void Button::draw(gdl::AShader & shader, gdl::Clock const& clock)
{
  if (_cursor == true)
    c->draw(shader, clock);
  AWidget::draw(shader, clock);
}
