#include "GameScene.hh"
#include "ScoreMenu.hh"

#include <iostream>
#include <stack>

Scoring& ScoreMenu::_scoring = Scoring::getInstance();
NumericChars& ScoreMenu::_num = NumericChars::getInstance();

ScoreMenu::ScoreMenu(SceneArguments const& arg)
  : AMenuScene("ScoreMenu"), _args(*new SceneArguments()), _scorp1(_scoring.getScoresP1()), _scorp2(_scoring.getScoresP2())
{
  _args.set("width", arg.get("width"));
  _args.set("file", arg.get("file"));
  _args.set("height", arg.get("height"));
  _args.set("players", arg.get("players"));
  _args.set("ai", arg.get("ai"));

  p1 = new Cursor(ResourcesPath::asset("img/player1.tga"), glm::vec3(getXPercent(5), getYPercent(10), 1), glm::vec3(getXPercent(20), getYPercent(10), 0));
  p2 = new Cursor(ResourcesPath::asset("img/player2.tga"), glm::vec3(getXPercent(60), getYPercent(10), 1), glm::vec3(getXPercent(20), getYPercent(10), 0));
}

ScoreMenu::~ScoreMenu()
{
  delete p1;
  delete p2;

}

bool ScoreMenu::initialize()
{
  setTexture(ResourcesPath::asset("img/sco.tga"));

  std::stack<std::string> tmp;
  std::stack<std::string> tmp2;
  std::string path;
  int x;
  int y;
  int i;

  if (p1->initialize() == false
      || p2->initialize() == false)
    return false;

  i = 0;
  y = 30;
  std::list<unsigned int>::iterator it = _scorp1.begin();
  while (it != _scorp1.end() || i < 5)
    {
      x = 5;
      tmp = _num.getTextures(*it);
      while (!tmp.empty())
	{
	  path = tmp.top();
	  _sc1.push_front(new Cursor(path, glm::vec3(getXPercent(x), getYPercent(y), 1), glm::vec3(getXPercent(10), getYPercent(10), 0)));
	  x+=7;
	  tmp.pop();
	}
      y += 10;
      it++;
      i++;
    }

  i = 0;
  y = 30;
  std::list<unsigned int>::iterator it3 = _scorp2.begin();
  while (it3 != _scorp2.end() || i < 5)
    {
      x = 60;
      tmp2 = _num.getTextures(*it3);
      while (!tmp2.empty())
	{
	  path = tmp2.top();
	  _sc2.push_front(new Cursor(path, glm::vec3(getXPercent(x), getYPercent(y), 1), glm::vec3(getXPercent(10), getYPercent(10), 0)));
	  x+=7;
	  tmp2.pop();
	}
      y += 10;
      it3++;
      i++;
    }

  std::list<Cursor*>::iterator it2 = _sc1.begin();
  while (it2 != _sc1.end())
    {
      (*it2)->initialize();
      it2++;
    }

  std::list<Cursor*>::iterator it4 = _sc2.begin();
  while (it4 != _sc2.end())
    {
      (*it4)->initialize();
      it4++;
    }

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

  p1->draw(shader, clock);
  p2->draw(shader, clock);


  std::list<Cursor*>::iterator it = _sc1.begin();
  while (it != _sc1.end())
    {
      (*it)->draw(shader, clock);
      it++;
    }

  std::list<Cursor*>::iterator it2 = _sc2.begin();
  while (it2 != _sc2.end())
    {
      (*it2)->draw(shader, clock);
      it2++;
    }

  return true;
}
