#include "OptionMenu.hh"

OptionMenu::OptionMenu(SceneArguments const& arg)
  : AMenuScene("OptionMenu")
{
  addButton("./build/assets/img/soundfx.tga", glm::vec3(60, 50, 1), glm::vec3(100, 100, 0) , static_cast<ButtonHandler>(&OptionMenu::soundfxhandler), 0);
  addButton("./build/assets/img/soundmusic.tga", glm::vec3(60, 180, 1), glm::vec3(100, 100, 0) , static_cast<ButtonHandler>(&OptionMenu::soundmusichandler), 1);
  addButton("./build/assets/img/back.tga", glm::vec3(60, 450, 1), glm::vec3(100, 100, 0) , static_cast<ButtonHandler>(&OptionMenu::backhandler), 2);

  _cursor = new Cursor("./build/assets/img/bombe.tga", glm::vec3(30, 100, 1), glm::vec3(50, 50, 0));

  _cursorFx = new Cursor("./build/assets/img/bombe.tga", glm::vec3(250, 70, 1), glm::vec3(50, 50, 0));
  _cursorMusic = new Cursor("./build/assets/img/bombe.tga", glm::vec3(250, 200, 1), glm::vec3(50, 50, 0));

}

OptionMenu::~OptionMenu()
{
  delete _cursor;
  delete _cursorFx;
  delete _cursorMusic;
}

bool OptionMenu::initialize()
{
  setTexture("./build/assets/img/menu.tga");
  AMenuScene::initialize();

  _cursor->initialize();
  _cursorFx->initialize();
  _cursorMusic->initialize();

  std::map<AWidget* , ButtonHandler>::iterator it;
  it = _mapButton.begin();

  while (it != _mapButton.end())
    {
      it->first->initialize();
      it++;
    }
  return true;
}

bool OptionMenu::update(gdl::Clock const& clock, gdl::Input& input)
{
  // j'avoue c'est crade mais il est 2h30 du mat' A REGLER
  if (input.getKey(SDLK_RIGHT))
    {

    }

  if (input.getKey(SDLK_LEFT))
    {

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

  glDisable(GL_DEPTH_TEST);
  glAlphaFunc(GL_GREATER, 0.3f);
  glEnable(GL_ALPHA_TEST);

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
}


