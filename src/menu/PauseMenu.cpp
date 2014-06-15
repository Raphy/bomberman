#include <iostream> // debug !

#include "MainMenu.hh"
#include "GameScene.hh"
#include "MapMenu.hh"
#include "OptionMenu.hh"
#include "PauseMenu.hh"
#include "GameAPI.hh"

SoundManager& PauseMenu::_son = SoundManager::getInstance();

PauseMenu::PauseMenu(SceneArguments const& arg)
  : AMenuScene("PauseMenu"), _arg(*new SceneArguments())
{
  _arg.set("width",arg.get("width"));
  _arg.set("file",arg.get("file"));
  _arg.set("players",arg.get("players"));
  _arg.set("height",arg.get("height"));
  _arg.set("ai",arg.get("ai"));

  addButton(ResourcesPath::asset("img/resume.tga"), glm::vec3(getXPercent(10), getYPercent(8), 1), glm::vec3(getXPercent(32), getYPercent(10), 0) , static_cast<ButtonHandler>(&PauseMenu::resumehandler), 0);
  addButton(ResourcesPath::asset("img/save.tga"), glm::vec3(getXPercent(10), getYPercent(20), 1), glm::vec3(getXPercent(25), getYPercent(10), 0) , static_cast<ButtonHandler>(&PauseMenu::savehandler), 1);
  addButton(ResourcesPath::asset("img/option.tga"), glm::vec3(getXPercent(10), getYPercent(32), 1), glm::vec3(getXPercent(32), getYPercent(10), 0) , static_cast<ButtonHandler>(&PauseMenu::optionhandler), 2);
  addButton(ResourcesPath::asset("img/exitmenu.tga"), glm::vec3(getXPercent(10), getYPercent(80), 1), glm::vec3(getXPercent(40), getYPercent(10), 0) , static_cast<ButtonHandler>(&PauseMenu::exitmenuhandler), 3);

  _cursor = new Cursor(ResourcesPath::asset("img/bombe.tga"), glm::vec3(getXPercent(7), getYPercent(8), 1), glm::vec3(getXPercent(5), getYPercent(5), 0));
  _save = new Cursor(ResourcesPath::asset("img/gamesave.tga"), glm::vec3(getXPercent(51), getYPercent(20), 1), glm::vec3(getXPercent(46), getYPercent(11), 0));
}

PauseMenu::~PauseMenu()
{
  delete _cursor;
  delete _save;
}

bool PauseMenu::initialize()
{
  setTexture(ResourcesPath::asset("img/pausemenu.tga"));
  if (AMenuScene::initialize() == false
      || _cursor->initialize() == false
      || _save->initialize() == false)
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

  _son.pause();

  return true;
}

bool PauseMenu::update(gdl::Clock const& clock, gdl::Input& input)
{

  if (input.getKey(SDLK_UP) && !_btnUp)
    {
      _isSave = false;
      _son.playFx("button");
      _cursorPos--;
      _btnUp = true;
      if (_cursorPos < 0)
	_cursorPos = 3;
    }
  else if (!input.getKey(SDLK_UP) && _btnUp)
    _btnUp = false;

  if (input.getKey(SDLK_DOWN) && !_btnDown)
    {
      _isSave = false;
      _son.playFx("button");
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

bool PauseMenu::draw(gdl::AShader& shader, gdl::Clock const &clock)
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
  if (_isSave == true)
    _save->draw(shader, clock);
  return true;
}

void PauseMenu::resumehandler(int a)
{
  _son.resume();
  setStatusBack();
}

void PauseMenu::savehandler(int a)
{
  _isSave = true;
  GameAPI::getInstance().save(ResourcesPath::save("save.bmap"));
}

void PauseMenu::optionhandler(int a)
{
  setStatusGoOn<OptionMenu>(*new SceneArguments(_arg));
}

void PauseMenu::exitmenuhandler(int a)
{
  setStatusGoOn<MainMenu>(*new SceneArguments(_arg));
}
