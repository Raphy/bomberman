#include "GameScene.hh"
#include "MapMenu.hh"
#include "LoadingMenu.hh"

LoadingMenu::LoadingMenu(SceneArguments const& arg)
  : AMenuScene("LoadMenu"), _args(*new SceneArguments())
{
  _args.set("width", arg.get("width"));
  _args.set("file", arg.get("file"));
  _args.set("height", arg.get("height"));
  _args.set("players", arg.get("players"));
  _args.set("ai", arg.get("ai"));
}

LoadingMenu::~LoadingMenu()
{

}

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
