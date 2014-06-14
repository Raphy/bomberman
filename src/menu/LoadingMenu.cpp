#include "GameScene.hh"
#include "MapMenu.hh"
#include "LoadingMenu.hh"

LoadingMenu::LoadingMenu(SceneArguments const& arg)
  : AMenuScene("LoadMenu"), _args(*new SceneArguments())
{
  _args = arg;
}

LoadingMenu::~LoadingMenu()
{}

bool LoadingMenu::initialize()
{
  setTexture(ResourcesPath::asset("img/loading.tga"));

  if (AMenuScene::initialize() == false)
    {
      return false;
    }
  return true;
}

bool LoadingMenu::update(gdl::Clock const& clock, gdl::Input& input)
{
  setStatusGoOn<GameScene>(_args);
  return true;
}

bool LoadingMenu::draw(gdl::AShader& shader, gdl::Clock const&clock)
{
   AMenuScene::draw(shader, clock);
   return true;
}
