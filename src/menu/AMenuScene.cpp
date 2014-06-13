#include "AMenuScene.hh"

AMenuScene::AMenuScene(const std::string& tag)
  : AScene(tag), _conf() , _windowX((float)_conf.WindowWidth()), _windowY((float)_conf.WindowHeight())
{
  _projection = glm::ortho(0.0f, getWindowX(), getWindowY(), 0.0f, -1.0f, 1.0f);

  _cursorPos = 0;

  _camera = new Camera();
}

AMenuScene::~AMenuScene()
{
  std::map<AWidget*, ButtonHandler>::iterator it = _mapButton.begin();

  while (it != _mapButton.end())
    {
      delete it->first;
      _mapButton.erase(it);
      it++;
    }
  delete _camera;
}

bool AMenuScene::initialize()
{
  if (_texture.load(_pathTexture) == false)
    {
      std::cerr << "Cannot load the background texture" << std::endl;
      return false;
    }

  if (_camera->initialize() == false)
    {
      return false;
    }

  _camera->setPosition(glm::vec3(0, 0, 0));
  _camera->setLookAt(glm::vec3(0, 0, 1));

  addCamera("menu", _camera);

  _geometry.setColor(glm::vec4(1,1, 1, 1));

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

bool AMenuScene::update(gdl::Clock const& clock, gdl::Input& input)
{
  return true;
}

bool AMenuScene::draw(gdl::AShader& shader, gdl::Clock const& clock)
{
  shader.bind();
  shader.setUniform("view", glm::mat4(1));
  shader.setUniform("projection", _projection);

  glm::vec3 size(getWindowX(), getWindowY(), 0);
  glm::mat4 transform(1);

  transform = glm::scale(transform, size);
  _texture.bind();
  _geometry.draw(shader, transform, GL_QUADS);

  _camera->draw(shader, clock);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return true;
}

void AMenuScene::setTexture(const std::string& path)
{
  _pathTexture = path;
}

void AMenuScene::addButton(const std::string& path,  const glm::vec3& pos, const glm::vec3& scale, const ButtonHandler& fct, int c)
{
  _mapButton.insert(std::pair<AWidget*, ButtonHandler>(new AWidget(path, pos, scale, c), fct));
}

float AMenuScene::getWindowX() const
{
  return _windowX;
}

float AMenuScene::getWindowY() const
{
  return _windowY;
}

float AMenuScene::getXPercent(float p) const
{
  return (getWindowX() * p) / 100;
}

float AMenuScene::getYPercent(float p) const
{
  return (getWindowY() * p) / 100;
}
