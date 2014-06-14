#include "OptionMenu.hh"
#include "SceneStatus.hh"

SoundManager& OptionMenu::_son = SoundManager::getInstance();

OptionMenu::OptionMenu(SceneArguments const& arg)
  : AMenuScene("OptionMenu")
{
  addButton(ResourcesPath::asset("img/soundfx.tga"), glm::vec3(getXPercent(8), getYPercent(8), 1), glm::vec3(getXPercent(25), getYPercent(8), 0) , static_cast<ButtonHandler>(&OptionMenu::soundfxhandler), 0);
  addButton(ResourcesPath::asset("img/soundmusic.tga"), glm::vec3(getXPercent(8), getYPercent(20), 1), glm::vec3(getXPercent(25), getYPercent(8), 0), static_cast<ButtonHandler>(&OptionMenu::soundmusichandler), 1);

  addButton(ResourcesPath::asset("img/muteall.tga"), glm::vec3(getXPercent(8), getYPercent(44), 1), glm::vec3(getXPercent(20), getYPercent(6), 0) , static_cast<ButtonHandler>(&OptionMenu::mutehandler), 2);

  addButton(ResourcesPath::asset("img/back.tga"), glm::vec3(getXPercent(8), getYPercent(80), 1), glm::vec3(getXPercent(20), getYPercent(8), 0) , static_cast<ButtonHandler>(&OptionMenu::backhandler), 3);

  _cursorbsonfx = new Cursor( ResourcesPath::asset("img/barson.tga"), glm::vec3(getXPercent(37), getYPercent(10), 1), glm::vec3(getXPercent(64), getYPercent(4), 0));
  _cursorbsonmusic = new Cursor( ResourcesPath::asset("img/barson.tga"), glm::vec3(getXPercent(37), getYPercent(22), 1), glm::vec3(getXPercent(64), getYPercent(4), 0));

  _cursor = new Cursor(ResourcesPath::asset("img/bombe.tga"), glm::vec3(getXPercent(5), getYPercent(8), 1), glm::vec3(getXPercent(5), getYPercent(5), 0));

  _cursormute = new Cursor(ResourcesPath::asset("img/mute.tga"), glm::vec3(getXPercent(38), getYPercent(42), 1), glm::vec3(getXPercent(10), getYPercent(10), 0));
  _cursorson = new Cursor(ResourcesPath::asset("img/son.tga"), glm::vec3(getXPercent(38), getYPercent(42), 1), glm::vec3(getXPercent(10), getYPercent(10), 0));

  _cursorFx = new Cursor(ResourcesPath::asset("img/dynamite.tga"), glm::vec3(getXPercent(getPosWithSoundFx()), getYPercent(9), 1), glm::vec3(getXPercent(1), getYPercent(7), 0));
  _cursorMusic = new Cursor(ResourcesPath::asset("img/dynamite.tga"), glm::vec3(getXPercent(getPosWithSoundMusic()), getYPercent(21), 1), glm::vec3(getXPercent(1), getYPercent(7), 0));

}

OptionMenu::~OptionMenu()
{
  delete _cursormute;
  delete _cursorson;
  delete _cursorbsonfx;
  delete _cursorbsonmusic;
  delete _cursor;
  delete _cursorFx;
  delete _cursorMusic;
}

bool OptionMenu::initialize()
{
  setTexture(ResourcesPath::asset("img/optiontheme.tga"));
  if (AMenuScene::initialize() == false
      || _cursor->initialize() == false
      || _cursorbsonfx->initialize() == false
      || _cursorbsonmusic->initialize() == false
      || _cursorFx->initialize() == false
      || _cursormute->initialize() == false
      || _cursorson->initialize() == false
      || _cursorMusic->initialize() == false) {
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

bool OptionMenu::update(gdl::Clock const& clock, gdl::Input& input)
{
  glm::vec3 tmp;

  if (input.getKey(SDLK_RIGHT))
    {
      _son.playFx("button");
      if (_cursorPos == 0)
	{
	  if (_son.getVolumeFx() <= 126 && _son.isMute() == false)
	    {
	      OptionMenu::soundfxhandler(1);
	      tmp = _cursorFx->getPosition();
	      tmp.x = tmp.x + getXPercent(1);
	      _cursorFx->setPosX(tmp);
	    }
	}
      else if (_cursorPos == 1)
	{
	  if (_son.getVolumeMusic() <= 126 && _son.isMute() == false)
	    {
	      OptionMenu::soundmusichandler(1);
	      tmp = _cursorMusic->getPosition();
	      tmp.x = tmp.x + getXPercent(1);
	      _cursorMusic->setPosX(tmp);
	    }
	}
    }

  if (input.getKey(SDLK_LEFT))
    {
      _son.playFx("button");
      if (_cursorPos == 0)
	{
	  if (_son.getVolumeFx() >= 2 && _son.isMute() == false)
	    {
	      OptionMenu::soundfxhandler(-1);
	      tmp = _cursorFx->getPosition();
	      tmp.x = tmp.x - getXPercent(1);
	      _cursorFx->setPosX(tmp);
	    }
	}
      else if (_cursorPos == 1)
	{
	  if (_son.getVolumeMusic() >= 2 && _son.isMute() == false)
	    {
	      OptionMenu::soundmusichandler(-1);
	      tmp = _cursorMusic->getPosition();
	      tmp.x = tmp.x - getXPercent(1);
	      _cursorMusic->setPosX(tmp);
	    }
	}
    }

  if (input.getKey(SDLK_UP) && !_btnUp)
    {
      _son.playFx("button");
      _cursorPos--;
      _btnUp = true;
      if (_cursorPos < 0)
	_cursorPos = 3;
    }
  if (!input.getKey(SDLK_UP) && _btnUp)
    _btnUp = false;

  if (input.getKey(SDLK_DOWN) && !_btnDown)
    {
      _son.playFx("button");
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
  if (!input.getKey(SDLK_SPACE) && _btnSpace)
    _btnSpace = false;
  return true;
}

bool OptionMenu::draw(gdl::AShader& shader, gdl::Clock const &clock)
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

  if (_son.isMute() == true)
    _cursormute->draw(shader, clock);
  else if (_son.isMute() == false)
    _cursorson->draw(shader, clock);

  _cursor->draw(shader, clock);

  _cursorFx->draw(shader, clock);
  _cursorMusic->draw(shader, clock);

  _cursorbsonfx->draw(shader, clock);
  _cursorbsonmusic->draw(shader, clock);

  return true;
}

void OptionMenu::soundfxhandler(int a)
{
  if (a == 1)
    _son.setVolumeFx(_son.getVolumeFx() + 2);
  else
    _son.setVolumeFx(_son.getVolumeFx() - 2);
}

void OptionMenu::soundmusichandler(int a)
{
  if (a == 1)
    _son.setVolumeMusic(_son.getVolumeMusic() + 2);
  else
    _son.setVolumeMusic(_son.getVolumeMusic() - 2);
}

void OptionMenu::backhandler(int a)
{
  setStatusBack();
}

void OptionMenu::mutehandler(int a)
{
  _son.mute();
}

float OptionMenu::getPosWithSoundMusic() const
{
  int t = _son.getVolumeMusic();
  float a;

  a = ((float)t / 2) + 37;

  return (float)a;
}

float OptionMenu::getPosWithSoundFx() const
{
  int t = _son.getVolumeFx();
  float a;

  a = ((float)t / 2) + 37;

  return (float)a;
}
