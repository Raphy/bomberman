#include <iostream>

#include "MainMenu.hh"

MainMenu::MainMenu(SceneArguments const&)
  : AMenuScene("mainMenu")
{
}

MainMenu::~MainMenu()
{
}

bool MainMenu::initialize()
{
  setTexture("./build/assets/img/menu.tga");

  AMenuScene::initialize();


  return true;
}

bool MainMenu::update(gdl::Clock const& clock, gdl::Input& input)
{
  return true;
}

bool MainMenu::draw(gdl::AShader & shader, gdl::Clock const &clock)
{
  AMenuScene::draw(shader, clock);


  return true;
}
