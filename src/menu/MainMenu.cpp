#include <iostream> // debug !

#include "MainMenu.hh"
#include "GameScene.hh"
#include "MapMenu.hh"
#include "OptionMenu.hh"



MainMenu::MainMenu(SceneArguments const& arg)
  : AMenuScene("MainMenu")
{
  addButton(ResourcesPath::asset("img/play.tga"), glm::vec3(60, 50, 1), glm::vec3(150, 70, 0) , static_cast<ButtonHandler>(&MainMenu::playhandler), 0);
  addButton(ResourcesPath::asset("img/option.tga"), glm::vec3(60, 130, 1), glm::vec3(180, 70, 0) , static_cast<ButtonHandler>(&MainMenu::optionhandler), 1);
  addButton(ResourcesPath::asset("img/load.tga"), glm::vec3(60, 210, 1), glm::vec3(150, 70, 0) , static_cast<ButtonHandler>(&MainMenu::loadhandler), 2);
  addButton(ResourcesPath::asset("img/exit.tga"), glm::vec3(60, 450, 1), glm::vec3(150, 70, 0) , static_cast<ButtonHandler>(&MainMenu::exithandler), 3);

  _cursor = new Cursor(ResourcesPath::asset("img/bombe.tga"), glm::vec3(30, 100, 1), glm::vec3(30, 40, 0));

}

MainMenu::~MainMenu()
{
  delete _cursor;
}

bool MainMenu::initialize()
{
  setTexture(ResourcesPath::asset("img/menu.tga"));
  if (AMenuScene::initialize() == false
      || _cursor->initialize() == false)
    {
      return false;
    }

  std::map<AWidget* , ButtonHandler>::iterator it = _mapButton.begin();

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

bool MainMenu::update(gdl::Clock const& clock, gdl::Input& input)
{
  if (input.getKey(SDLK_UP) && !_btnUp)
    {
      _cursorPos--;
      _btnUp = true;
      if (_cursorPos < 0)
	_cursorPos = 3;
    }
  else if (!input.getKey(SDLK_UP) && _btnUp)
    _btnUp = false;

  if (input.getKey(SDLK_DOWN) && !_btnDown)
    {
      _btnDown = true;
      _cursorPos++;
      if (_cursorPos == 4)
	_cursorPos = 0;
    }
  else if (!input.getKey(SDLK_DOWN) && _btnDown)
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
  else if (!input.getKey(SDLK_SPACE) && _btnSpace)
    _btnSpace = false;

  return true;
}

bool MainMenu::draw(gdl::AShader& shader, gdl::Clock const &clock)
{
  AMenuScene::draw(shader, clock);

  std::map<AWidget* , ButtonHandler>::iterator it = _mapButton.begin();
  glm::vec3 tmp;

  while (it != _mapButton.end())
    {
      if (it->first->getCur() == _cursorPos)
	{
	  tmp = it->first->getPos();
	  tmp.y += 15;
	  _cursor->setPosY(tmp);
	}
      it->first->draw(shader, clock);
      it++;
    }
  _cursor->draw(shader, clock);

  return true;
}

void MainMenu::playhandler(int t)
{
  SceneArguments& args = *new SceneArguments();
  setStatusGoOn<MapMenu>(args);
}

void MainMenu::optionhandler(int t)
{
  setStatusGoOn<OptionMenu>(*new SceneArguments());
}

void MainMenu::exithandler(int t)
{
  setStatusBack();
}

void MainMenu::loadhandler(int t)
{
  SceneArguments& args = *new SceneArguments();
  args.set("file", ResourcesPath::save("save.bmap"));
  setStatusGoOn<GameScene>(args);
}
