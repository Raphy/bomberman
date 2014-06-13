#include "OptionMenu.hh"
#include "SceneStatus.hh"

SoundManager& OptionMenu::_son = SoundManager::getInstance();

OptionMenu::OptionMenu(SceneArguments const& arg)
  : AMenuScene("OptionMenu")
{
  addButton(ResourcesPath::asset("img/soundfx.tga"), glm::vec3(60, 50, 1), glm::vec3(180, 100, 0) , static_cast<ButtonHandler>(&OptionMenu::soundfxhandler), 0);
  addButton(ResourcesPath::asset("img/soundmusic.tga"), glm::vec3(60, 180, 1), glm::vec3(180, 100, 0) , static_cast<ButtonHandler>(&OptionMenu::soundmusichandler), 1);
  addButton(ResourcesPath::asset("img/back.tga"), glm::vec3(60, 450, 1), glm::vec3(100, 100, 0) , static_cast<ButtonHandler>(&OptionMenu::backhandler), 2);

  _cursorbsonfx = new Cursor( ResourcesPath::asset("img/barson.tga"), glm::vec3(300, 100, 1), glm::vec3(300, 20, 0));
  _cursorbsonmusic = new Cursor( ResourcesPath::asset("img/barson.tga"), glm::vec3(300, 200, 1), glm::vec3(300, 20, 0));

  _cursor = new Cursor(ResourcesPath::asset("img/bombe.tga"), glm::vec3(30, 100, 1), glm::vec3(50, 50, 0));
  _cursorFx = new Cursor(ResourcesPath::asset("img/dynamite.tga"), glm::vec3(250, 85, 1), glm::vec3(10, 50, 0));
  _cursorMusic = new Cursor(ResourcesPath::asset("img/dynamite.tga"), glm::vec3(250, 200, 1), glm::vec3(10, 50, 0));

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
  setTexture(ResourcesPath::asset("img/menu.tga"));
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
  int v;

  if (input.getKey(SDLK_RIGHT))
    {

      if (_cursorPos == 0)
	{
	  tmp = _cursorFx->getPosition();
	  tmp.x = tmp.x + 2;
	  _cursorFx->setPosX(tmp);


	}
      else if (_cursorPos == 1)
	{
	  tmp = _cursorMusic->getPosition();
	  tmp.x = tmp.x + 2;
	  _cursorMusic->setPosX(tmp);


	  v = _son.getVolumeMusic();
	  v++;

	  _son.setVolumeMusic(v);

	}

    }

  if (input.getKey(SDLK_LEFT))
    {

      if (_cursorPos == 0)
	{
	  tmp = _cursorFx->getPosition();
	  tmp.x = tmp.x - 2;
	  _cursorFx->setPosX(tmp);



	}
      else if (_cursorPos == 1)
	{
	  tmp = _cursorMusic->getPosition();
	  tmp.x = tmp.x - 2;
	  _cursorMusic->setPosX(tmp);

	  v = _son.getVolumeMusic();
	  v--;

	  _son.setVolumeMusic(v);

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


