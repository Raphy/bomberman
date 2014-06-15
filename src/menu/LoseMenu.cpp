#include <iostream>

#include "MainMenu.hh"
#include "LoseMenu.hh"

LoseMenu::LoseMenu(SceneArguments const& arg)
  : AMenuScene("LoadMenu"), _time(0)
{

}

LoseMenu::~LoseMenu()
{

}

bool LoseMenu::initialize()
{
  setTexture(ResourcesPath::asset("img/lose.tga"));

  if (AMenuScene::initialize() == false)
    {
      return false;
    }
  return true;
}

bool LoseMenu::update(gdl::Clock const& clock, gdl::Input& input)
{
  _time += clock.getElapsed();
  if (_time > 8.0 || input.getKey(SDLK_ESCAPE))
    {
      setStatusGoOn<MainMenu>(*new SceneArguments());
    }
  return true;
}

bool LoseMenu::draw(gdl::AShader& shader, gdl::Clock const&clock)
{
   AMenuScene::draw(shader, clock);
   return true;
}
