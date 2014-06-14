#include "OptionMenu.hh"
#include "SceneStatus.hh"

SoundManager& OptionMenu::_son = SoundManager::getInstance();

OptionMenu::OptionMenu(SceneArguments const& arg)
  : AMenuScene("OptionMenu")
{
  addButton(ResourcesPath::asset("img/soundfx.tga"), glm::vec3(getXPercent(8), getYPercent(8), 1), glm::vec3(getXPercent(25), getYPercent(8), 0) , static_cast<ButtonHandler>(&OptionMenu::soundfxhandler), 0);
  addButton(ResourcesPath::asset("img/soundmusic.tga"), glm::vec3(getXPercent(8), getYPercent(20), 1), glm::vec3(getXPercent(25), getYPercent(8), 0), static_cast<ButtonHandler>(&OptionMenu::soundmusichandler), 1);
  addButton(ResourcesPath::asset("img/back.tga"), glm::vec3(getXPercent(8), getYPercent(80), 1), glm::vec3(getXPercent(20), getYPercent(8), 0) , static_cast<ButtonHandler>(&OptionMenu::backhandler), 2);

  _cursorbsonfx = new Cursor( ResourcesPath::asset("img/barson.tga"), glm::vec3(getXPercent(37), getYPercent(10), 1), glm::vec3(getXPercent(64), getYPercent(4), 0));
  _cursorbsonmusic = new Cursor( ResourcesPath::asset("img/barson.tga"), glm::vec3(getXPercent(37), getYPercent(22), 1), glm::vec3(getXPercent(64), getYPercent(4), 0));

  _cursor = new Cursor(ResourcesPath::asset("img/bombe.tga"), glm::vec3(getXPercent(5), getYPercent(8), 1), glm::vec3(getXPercent(5), getYPercent(5), 0));

  _cursorFx = new Cursor(ResourcesPath::asset("img/dynamite.tga"), glm::vec3(getXPercent(getPosWithSoundFx()), getYPercent(9), 1), glm::vec3(getXPercent(1), getYPercent(7), 0));
  _cursorMusic = new Cursor(ResourcesPath::asset("img/dynamite.tga"), glm::vec3(getXPercent(getPosWithSoundMusic()), getYPercent(21), 1), glm::vec3(getXPercent(1), getYPercent(7), 0));

}

OptionMenu::~OptionMenu()
{
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
      if (_cursorPos == 0)
	{
	  if (_son.getVolumeFx() <= 126)
	    {
	      _son.setVolumeFx(_son.getVolumeFx() + 2);
	      tmp = _cursorFx->getPosition();
	      tmp.x = tmp.x + getXPercent(1);
	      _cursorFx->setPosX(tmp);
	    }
	}
      else if (_cursorPos == 1)
	{
	  if (_son.getVolumeMusic() <= 126)
	    {
	      _son.setVolumeMusic(_son.getVolumeMusic() + 2);
	      tmp = _cursorMusic->getPosition();
	      tmp.x = tmp.x + getXPercent(1);
	      _cursorMusic->setPosX(tmp);
	    }
	}
    }


  if (input.getKey(SDLK_LEFT))
    {

      if (_cursorPos == 0)
	{
	  if (_son.getVolumeFx() >= 2)
	    {
	      _son.setVolumeFx(_son.getVolumeFx() - 2);
	      tmp = _cursorFx->getPosition();
	      tmp.x = tmp.x - getXPercent(1);
	      _cursorFx->setPosX(tmp);
	    }
	}
      else if (_cursorPos == 1)
	{
	  if (_son.getVolumeMusic() >= 2)
	    {
	      _son.setVolumeMusic(_son.getVolumeMusic() - 2);
	      tmp = _cursorMusic->getPosition();
	      tmp.x = tmp.x - getXPercent(1);
	      _cursorMusic->setPosX(tmp);
	    }
	}
    }


  if (input.getKey(SDLK_UP) && !_btnUp)
    {
      _cursorPos--;
      _btnUp = true;
      if (_cursorPos < 0)
	_cursorPos = 2;
    }
  if (!input.getKey(SDLK_UP) && _btnUp)
    _btnUp = false;

  if (input.getKey(SDLK_DOWN) && !_btnDown)
    {
      _btnDown = true;
      _cursorPos++;
      if (_cursorPos == 3)
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

  _cursor->draw(shader, clock);

  _cursorFx->draw(shader, clock);
  _cursorMusic->draw(shader, clock);

  _cursorbsonfx->draw(shader, clock);
  _cursorbsonmusic->draw(shader, clock);



  return true;
}

void OptionMenu::soundfxhandler(int t)
{
  std::cout << "sound FX handler ok\n";
}

void OptionMenu::soundmusichandler(int t)
{
  std::cout << "sound MUSIC handler ok\n";
}

void OptionMenu::backhandler(int t)
{
  std::cout << "back handler ok\n";

  setStatusBack();
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
  int t = _son.getVolumeMusic();
  float a;

  a = ((float)t / 2) + 37;

  return (float)a;
}
