#include <iostream>

#include "MainMenu.hh"
#include "GameScene.hh"
#include "MapMenu.hh"
#include "OptionMenu.hh"
#include "LoadingMenu.hh"
#include "PlayerMenu.hh"

SoundManager& MainMenu::_son = SoundManager::getInstance();

MainMenu::MainMenu(SceneArguments const& arg)
  : AMenuScene("MainMenu"), _playlist(), _arg(*new SceneArguments())
{
  _arg.set("width",arg.get("width"));
  _arg.set("file",arg.get("file"));
  _arg.set("players",arg.get("players"));
  _arg.set("height",arg.get("height"));
  _arg.set("ai",arg.get("ai"));

  addButton(ResourcesPath::asset("img/play.tga"), glm::vec3(getXPercent(8), getYPercent(8), 1), glm::vec3(getXPercent(20), getYPercent(10), 0) , static_cast<ButtonHandler>(&MainMenu::playhandler), 0);
  addButton(ResourcesPath::asset("img/option.tga"), glm::vec3(getXPercent(8), getYPercent(20), 1), glm::vec3(getXPercent(25), getYPercent(10), 0) , static_cast<ButtonHandler>(&MainMenu::optionhandler), 1);
  addButton(ResourcesPath::asset("img/load.tga"), glm::vec3(getXPercent(8), getYPercent(32), 1), glm::vec3(getXPercent(20), getYPercent(10), 0) , static_cast<ButtonHandler>(&MainMenu::loadhandler), 2);
  addButton(ResourcesPath::asset("img/score.tga"), glm::vec3(getXPercent(8), getYPercent(44), 1), glm::vec3(getXPercent(22), getYPercent(10), 0) , static_cast<ButtonHandler>(&MainMenu::scorehandler), 3);
  addButton(ResourcesPath::asset("img/exit.tga"), glm::vec3(getXPercent(8), getYPercent(80), 1), glm::vec3(getXPercent(10), getYPercent(10), 0) , static_cast<ButtonHandler>(&MainMenu::exithandler), 4);

  _cursor = new Cursor(ResourcesPath::asset("img/bombe.tga"), glm::vec3(getXPercent(5), getYPercent(8), 1), glm::vec3(getXPercent(5), getYPercent(5), 0));
}

MainMenu::~MainMenu()
{
  delete _cursor;
}

void MainMenu::initPlaylist()
{
  _playlist.deletePlaylist();
  _playlist.addPlaylist("menu");
  _playlist.playPlaylist();
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

  initPlaylist();

  return true;
}

bool MainMenu::update(gdl::Clock const& clock, gdl::Input& input)
{
  _playlist.update();

  if (input.getKey(SDLK_UP) && !_btnUp)
    {
      _son.playFx("button");
      _cursorPos--;
      _btnUp = true;
      if (_cursorPos < 0)
	_cursorPos = 4;
    }
  else if (!input.getKey(SDLK_UP) && _btnUp)
    _btnUp = false;

  if (input.getKey(SDLK_DOWN) && !_btnDown)
    {
      _son.playFx("button");
      _btnDown = true;
      _cursorPos++;
      if (_cursorPos == 5)
	_cursorPos = 0;
    }
  else if (!input.getKey(SDLK_DOWN) && _btnDown)
    _btnDown = false;

  if (input.getKey(SDLK_SPACE) && !_btnSpace)
    {
      std::map<AWidget* , ButtonHandler>::iterator it;
      _son.playFx("button");
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
  (void)t;
  setStatusGoOn<PlayerMenu>(*new SceneArguments(_arg));
}

void MainMenu::optionhandler(int t)
{
  (void)t;
  setStatusGoOn<OptionMenu>(*new SceneArguments(_arg));
}

void MainMenu::exithandler(int t)
{
  (void)t;
  setStatusLeave();
}

void MainMenu::loadhandler(int t)
{
  (void)t;
  _arg.set("file", ResourcesPath::save("save.bmap"));
  setStatusGoOn<LoadingMenu>(*new SceneArguments(_arg));
}

void MainMenu::scorehandler(int t)
{
  (void)t;
  setStatusGoOn<ScoreMenu>(*new SceneArguments(_arg));
}
