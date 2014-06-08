#include "MenuScene.hh"

const std::string MenuScene::Tag = "menu";

MenuScene::MenuScene(/*SceneArguments const& args*/)
  : AScene(Tag)
{
  _projection = glm::ortho(0.0f, 600.0f, 600.0f, 0.0f, -1.0f, 1.0f); // taille ecran
  _transformation = glm::mat4(1);

  /* Set elem of Button*/

  _listButton.push_back(new AWidget(false, "./build/assets/img/play.tga", glm::vec3(20, 100, 1), glm::vec3(100, 100, 0)));
  _listButton.push_back(new AWidget(false, "./build/assets/img/option.tga", glm::vec3(20, 250, 1), glm::vec3(100, 100, 0)));
  _listButton.push_back(new AWidget(false, "./build/assets/img/exit.tga", glm::vec3(20, 450, 1), glm::vec3(100, 80, 0)));


}

MenuScene::~MenuScene()
{
}

bool MenuScene::initialize()
{
  if (_texture.load("./build/assets/img/menu.tga") == false)
    {
      std::cerr << "Cannot load the wall texture" << std::endl;
      return (false);
    }
  std::vector<AWidget*>::iterator it = _listButton.begin();

  while (it != _listButton.end())
    {
      (*it)->initialize();
      it++;
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

bool MenuScene::update(gdl::Clock const& clock, gdl::Input& input)
{
  return true;
}

bool MenuScene::draw(gdl::AShader& shader, gdl::Clock const& clock)
{
  (void)clock;

  shader.bind();
  shader.setUniform("view", _transformation);
  shader.setUniform("projection", _projection);

  glm::vec3 size(600, 600, 0); // taille img final
  glm::mat4 transform(1);

  transform = glm::scale(transform, size);

  _texture.bind();

  _geometry.draw(shader, transform, GL_QUADS);


  std::vector<AWidget*>::iterator it = _listButton.begin();


  while (it != _listButton.end())
    {
      (*it)->draw(shader, clock);
      it++;
    }

  return true;
}
