
#include <iostream>

#include "GameScene.hh"
#include "MapMenu.hh"
#include "LoadingMenu.hh"

LoadingMenu::LoadingMenu(SceneArguments const& arg)
  : AMenuScene("LoadMenu")
{
  std::cout << "FILE = "<< arg.get("file") << std::endl;
  std::cout << "heigth = "<< arg.get("height") << std::endl;
  std::cout << "WIDTH  = "<< arg.get("width") << std::endl;


}

LoadingMenu::~LoadingMenu()
{
  //  delete &_args;
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
  SceneArguments& args = *new SceneArguments();
  args.set("file", ResourcesPath::map("map1.bmap"));
  setStatusGoOn<GameScene>(args);

  //  setStatusGoOn<GameScene>(*new SceneArguments());
  return true;
}

bool LoadingMenu::draw(gdl::AShader& shader, gdl::Clock const&clock)
{
   AMenuScene::draw(shader, clock);
   return true;
}
