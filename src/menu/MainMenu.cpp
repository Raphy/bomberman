
#include <iostream> // debug !

#include "MainMenu.hh"

// son ++!!

MainMenu::MainMenu(SceneArguments const& arg)
  : AMenuScene("MainMenu")
{
  addButton("./build/assets/img/play.tga", glm::vec3(60, 50, 1), glm::vec3(100, 100, 0) , static_cast<ButtonHandler>(&MainMenu::playhandler), 0);
  addButton("./build/assets/img/option.tga", glm::vec3(60, 180, 1), glm::vec3(100, 100, 0) , static_cast<ButtonHandler>(&MainMenu::optionhandler), 1);
  addButton("./build/assets/img/load.tga", glm::vec3(60, 300, 1), glm::vec3(100, 100, 0) , static_cast<ButtonHandler>(&MainMenu::exithandler), 2);
  addButton("./build/assets/img/exit.tga", glm::vec3(60, 450, 1), glm::vec3(100, 100, 0) , static_cast<ButtonHandler>(&MainMenu::exithandler), 3);

  _cursor = new Cursor("./build/assets/img/bombe.tga", glm::vec3(30, 100, 1), glm::vec3(50, 50, 0));

}

MainMenu::~MainMenu()
{
  delete _cursor;
}

bool MainMenu::initialize()
{
  setTexture("./build/assets/img/menu.tga");
  AMenuScene::initialize();

  _cursor->initialize();

  std::map<AWidget* , ButtonHandler>::iterator it;
  it = _mapButton.begin();

  while (it != _mapButton.end())
    {
      it->first->initialize();
      it++;
    }
  return true;
}

bool MainMenu::update(gdl::Clock const& clock, gdl::Input& input)
{
  // j'avoue c'est crade mais il est 2h30 du mat' A REGLER

  if (input.getKey(SDLK_UP) && !_btnUp)
    {
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
	    (this->*(it->second))();
	  it++;
	}
    }
  if (!input.getKey(SDLK_SPACE) && _btnSpace)
    _btnSpace = false;
  return true;
}

bool MainMenu::draw(gdl::AShader& shader, gdl::Clock const &clock)
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

  return true;
}

void MainMenu::playhandler()
{
  std::cout << "PLAY handler ok\n";
}

void MainMenu::optionhandler()
{
  std::cout << "OPTION handler ok\n";
}

void MainMenu::exithandler()
{
  std::cout << "EXIT handler ok\n";
}

void MainMenu::loadhandler()
{
  std::cout << "LOAD handler ok\n";
}
