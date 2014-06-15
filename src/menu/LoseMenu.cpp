#include <iostream>

#include "MainMenu.hh"
#include "LoseMenu.hh"

LoseMenu::LoseMenu(SceneArguments const& arg)
  : AMenuScene("LoadMenu"), _time(0), _arg(*new SceneArguments())
{
  _arg.set("width",arg.get("width"));
  _arg.set("height",arg.get("height"));
  _arg.set("ai",arg.get("ai"));
  _arg.set("players",arg.get("players"));
  _arg.set("file",arg.get("file"));
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
      setStatusGoOn<MainMenu>(*new SceneArguments(_arg));
    }
  return true;
}

bool LoseMenu::draw(gdl::AShader& shader, gdl::Clock const&clock)
{
   AMenuScene::draw(shader, clock);
   return true;
}
