#include <string>
#include "PlayerMenu.hh"
#include "MapMenu.hh"
#include "LoadingMenu.hh"

SoundManager& PlayerMenu::_son = SoundManager::getInstance();

PlayerMenu::PlayerMenu(SceneArguments const& arg)
  : AMenuScene("PlayerMenu")
{
  addButton(ResourcesPath::asset("img/nbplayer.tga"), glm::vec3(getXPercent(8), getYPercent(10), 1), glm::vec3(getXPercent(45), getYPercent(15) ,0) ,  static_cast<ButtonHandler>(&PlayerMenu::nbplayerhandler), 0);
  addButton(ResourcesPath::asset("img/continue.tga"), glm::vec3(getXPercent(8), getYPercent(60), 1), glm::vec3(getXPercent(20), getYPercent(10) ,0) ,  static_cast<ButtonHandler>(&PlayerMenu::continuehandler), 1);
  addButton(ResourcesPath::asset("img/back.tga"), glm::vec3(getXPercent(8), getYPercent(80), 1), glm::vec3(getXPercent(20), getYPercent(10) ,0) ,  static_cast<ButtonHandler>(&PlayerMenu::backhandler), 2);

  _cursor = new Cursor(ResourcesPath::asset("img/bombe.tga"), glm::vec3(getXPercent(5), getYPercent(8), 1), glm::vec3(getXPercent(5), getYPercent(5) ,0));

  _nb1 = new Cursor(ResourcesPath::asset("img/alpha/1.tga"), glm::vec3(getXPercent(60), getYPercent(10), 1), glm::vec3(getXPercent(15), getYPercent(15) ,0));
  _nb2 = new Cursor(ResourcesPath::asset("img/alpha/2.tga"), glm::vec3(getXPercent(80), getYPercent(10), 1), glm::vec3(getXPercent(15), getYPercent(15) ,0));
  _nb1s = new Cursor(ResourcesPath::asset("img/alpha/1s.tga"), glm::vec3(getXPercent(60), getYPercent(10), 1), glm::vec3(getXPercent(15), getYPercent(15) ,0));
  _nb2s = new Cursor(ResourcesPath::asset("img/alpha/2s.tga"), glm::vec3(getXPercent(80), getYPercent(10), 1), glm::vec3(getXPercent(15), getYPercent(15) ,0));

}

PlayerMenu::~PlayerMenu()
{
  delete _cursor;
  delete _nb1;
  delete _nb2;
  delete _nb1s;
  delete _nb2s;
}

bool PlayerMenu::initialize()
{
  setTexture(ResourcesPath::asset("img/playermenu.tga"));
  if (AMenuScene::initialize() == false
      || _cursor->initialize() == false
      || _nb2->initialize() == false
      || _nb1->initialize() == false
      || _nb2s->initialize() == false
      || _nb1s->initialize() == false)
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

bool PlayerMenu::update(gdl::Clock const& clock, gdl::Input& input)
{

  if (_cursorPos == 0)
    {
      if (input.getKey(SDLK_LEFT) && _nbplayer == 2)
	_nbplayer = 1;
      else if (input.getKey(SDLK_RIGHT) && _nbplayer == 1)
	_nbplayer = 2;
    }


  if (input.getKey(SDLK_UP) && !_btnUp)
    {
      _son.playFx("button");
      _cursorPos--;
      _btnUp = true;
      if (_cursorPos < 0)
	_cursorPos = 2;
    }
  if (!input.getKey(SDLK_UP) && _btnUp)
    _btnUp = false;


  if (input.getKey(SDLK_DOWN) && !_btnDown)
    {
      _son.playFx("button");
      _btnDown = true;
      _cursorPos++;
      if (_cursorPos == 3)
	_cursorPos = 0;
    }
  if (!input.getKey(SDLK_DOWN) && _btnDown)
    _btnDown = false;


  if (input.getKey(SDLK_SPACE) && !_btnSpace)
    {
      _son.playFx("button");
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

bool PlayerMenu::draw(gdl::AShader& shader, gdl::Clock const &clock)
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
  if (_nbplayer == 1)
    {
      _nb1s->draw(shader, clock);
      _nb2->draw(shader, clock);
    }
  else
    {
      _nb1->draw(shader, clock);
      _nb2s->draw(shader, clock);
    }
  return true;
}

void PlayerMenu::backhandler(int t)
{
  setStatusBack();
}

void PlayerMenu::nbplayerhandler(int t)
{
}

void PlayerMenu::continuehandler(int t)
{
  SceneArguments& args = *new SceneArguments();
  args.set("players", std::to_string(_nbplayer));
  setStatusGoOn<MapMenu>(args);
}
