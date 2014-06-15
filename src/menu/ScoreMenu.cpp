#include "GameScene.hh"
#include "ScoreMenu.hh"

ScoreMenu::ScoreMenu(SceneArguments const& arg)
  : AMenuScene("ScoreMenu"), _args(*new SceneArguments())
{
  _args.set("width", arg.get("width"));
  _args.set("file", arg.get("file"));
  _args.set("height", arg.get("height"));
  _args.set("players", arg.get("players"));
  _args.set("ai", arg.get("ai"));
}

ScoreMenu::~ScoreMenu()
{

}

bool ScoreMenu::initialize()
{
  setTexture(ResourcesPath::asset("img/save.tga"));

  if (AMenuScene::initialize() == false)
    {
      return false;
    }
  return true;
}

bool ScoreMenu::update(gdl::Clock const& clock, gdl::Input& input)
{
  if (input.getKey(SDLK_BACKSPACE))
    {
      setStatusBack();
    }

  return true;
}

bool ScoreMenu::draw(gdl::AShader& shader, gdl::Clock const&clock)
{
   AMenuScene::draw(shader, clock);
   return true;
}
