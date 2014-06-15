#include "MapMenu.hh"
#include "GameScene.hh"
#include "LoadingMenu.hh"

SoundManager& MapMenu::_son = SoundManager::getInstance();

MapMenu::MapMenu(SceneArguments const& arg)
  : AMenuScene("MapMenu")
{
  addButton(ResourcesPath::asset("img/map1.tga"), glm::vec3(60, 50, 1), glm::vec3(100, 100, 0) , static_cast<ButtonHandler>(&MapMenu::map1handler), 0);
  addButton(ResourcesPath::asset("img/map2.tga"), glm::vec3(60, 180, 1), glm::vec3(100, 100, 0) , static_cast<ButtonHandler>(&MapMenu::map2handler), 1);
  addButton(ResourcesPath::asset("img/maprandom.tga"), glm::vec3(60, 300, 1), glm::vec3(100, 100, 0) , static_cast<ButtonHandler>(&MapMenu::maprandomhandler), 2);
  addButton(ResourcesPath::asset("img/back.tga"), glm::vec3(60, 450, 1), glm::vec3(100, 100, 0) , static_cast<ButtonHandler>(&MapMenu::backhandler), 3);

  _cursor = new Cursor(ResourcesPath::asset("img/bombe.tga"), glm::vec3(30, 100, 1), glm::vec3(50, 50, 0));


}

MapMenu::~MapMenu()
{
  delete _cursor;
}

bool MapMenu::initialize()
{
  setTexture(ResourcesPath::asset("img/menu.tga"));
  if (AMenuScene::initialize() == false
      || _cursor->initialize() == false)
    {
      return false;
    }

  std::map<AWidget* , ButtonHandler>::iterator it;
  it = _mapButton.begin();

  while (it != _mapButton.end())
    {
      if (it->first->initialize() == false)
	{
	  return false;
	}
      it++;
    }
  return true;
}

bool MapMenu::update(gdl::Clock const& clock, gdl::Input& input)
{

  if (input.getKey(SDLK_UP) && !_btnUp)
    {
      setTexture(ResourcesPath::asset("img/menu.tga"));
      _cursorPos--;
      _btnUp = true;
      if (_cursorPos < 0)
	_cursorPos = 3;
    }
  if (!input.getKey(SDLK_UP) && _btnUp)
    _btnUp = false;


  if (input.getKey(SDLK_DOWN) && !_btnDown)
    {

      _btnDown = true;
      _cursorPos++;
      if (_cursorPos == 4)
	_cursorPos = 0;
    }
  if (!input.getKey(SDLK_DOWN) && _btnDown)
    _btnDown = false;


  if (input.getKey(SDLK_SPACE) && !_btnSpace)
    {
      std::map<AWidget* , ButtonHandler>::iterator it;

      _btnSpace = true;

      it = _mapButton.begin();
      while (it != _mapButton.end())
	{
	  if (it->first->getCur() == _cursorPos)
	    (this->*(it->second))(SDLK_SPACE);
	  it++;
	}

    }
  if (!input.getKey(SDLK_SPACE) && _btnSpace)
    _btnSpace = false;

  return true;
}

bool MapMenu::draw(gdl::AShader& shader, gdl::Clock const &clock)
{
  AMenuScene::draw(shader, clock);

  std::map<AWidget* , ButtonHandler>::iterator it;
  it = _mapButton.begin();

  while (it != _mapButton.end())
    {
      if (it->first->getCur() == _cursorPos)
	_cursor->setPosY(it->first->getPos());
      it->first->draw(shader, clock);
      it++;
    }

  _cursor->draw(shader, clock);


  return true;
}

void MapMenu::map1handler(int t)
{
  SceneArguments& args = *new SceneArguments();
  args.set("file", ResourcesPath::map("map1.bmap"));
  setStatusGoOn<LoadingMenu>(args);
}

void MapMenu::map2handler(int t)
{
  SceneArguments& args = *new SceneArguments();
  args.set("file", ResourcesPath::map("map2.bmap"));
  setStatusGoOn<LoadingMenu>(args);
}

void MapMenu::maprandomhandler(int t)
{
  SceneArguments& args = *new SceneArguments();
  args.set("width", "20");
  args.set("height", "20");
  args.set("players", "2");
  args.set("ai", "5");
  setStatusGoOn<LoadingMenu>(args);
}

void MapMenu::backhandler(int t)
{
  setStatusBack();
}

