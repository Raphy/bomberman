#include <iostream>

#include "AMenuScene.hh"


AMenuScene::AMenuScene(const std::string& tag)
  : AScene(tag)
{
  _projection = glm::ortho(0.0f, 600.0f, 600.0f, 0.0f, -1.0f, 1.0f); // taille ecran
  _transformation = glm::mat4(1);

  /* Set elem of Button*/
  /*
  _listButton.push_back(new Button(true, "./build/assets/img/play.tga", glm::vec3(60, 100, 1), glm::vec3(100, 100, 0), ));
  _listButton.push_back(new Button(false, "./build/assets/img/option.tga", glm::vec3(60, 250, 1), glm::vec3(100, 100, 0)));
  _listButton.push_back(new Button(false, "./build/assets/img/exit.tga", glm::vec3(60, 450, 1), glm::vec3(100, 80, 0)));
  */
}

AMenuScene::~AMenuScene()
{
  /*
  std::vector<AWidget*>::iterator it = _listButton.begin();

  while (it != _listButton.end())
    {
      _listButton.erase(it);
      delete *it;
      it++;
    }
  */
}

bool AMenuScene::initialize()
{

  if (_texture.load(_pathTexture) == false)
    {
      std::cerr << "Cannot load the wall texture" << std::endl;
      return (false);
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


  /*
    std::vector<AWidget*>::iterator it = _listButton.begin();

    while (it != _listButton.end())
    {
    (*it)->initialize();
    it++;
    }
  */
  std::cout << "Menu init\n";

  return true;
}

bool AMenuScene::update(gdl::Clock const& clock, gdl::Input& input)
{
  /*
  std::vector<AWidget*>::iterator it = _listButton.begin();

  while (it != _listButton.end())
    {
      (*it)->update(clock, input);
      it++;
    }
*/
  return true;
}

bool AMenuScene::draw(gdl::AShader& shader, gdl::Clock const& clock)
{
  shader.bind();
  shader.setUniform("view", _transformation);
  shader.setUniform("projection", _projection);

  glm::vec3 size(600, 600, 0); // taille img final BACKGROUND !!!!
  glm::mat4 transform(1);

  transform = glm::scale(transform, size);
  _texture.bind();
  _geometry.draw(shader, transform, GL_QUADS);

  /*  std::vector<AWidget*>::iterator it = _listButton.begin();
  while (it != _listButton.end())
    {
      (*it)->draw(shader, clock);
      it++;
    }
  */
  return true;
}

void AMenuScene::setTexture(const std::string& path)
{
  _pathTexture = path;
}
