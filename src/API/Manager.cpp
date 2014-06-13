//
// Manager.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Thu Jun  5 10:41:01 2014 raphael defreitas
// Last update Fri Jun 13 22:51:34 2014 raphael defreitas
//

#include	<lua.hpp>

#include	"game/GameScene.hh"
#include	"GameObject.hh"
#include	"Lua/Script.hh"
#include	"Manager.hh"
#include	"Map.hh"
#include	"Me.hh"
#include	"Player.hh"
#include	"Wall.hh"

using namespace API;
using namespace Lua;

Manager Manager::_instance = Manager();

Manager& Manager::getInstance(void)
{
  return _instance;
}

void Manager::registerScript(Script& script)
{
  GameObject::registerScript(script);
  Map::registerScript(script);
  Me::registerScript(script);
  Player::registerScript(script);
  API::Wall::registerScript(script);

  API::Map* udata = new API::Map();
  script.getVirtualMachine().setClass<API::Map>("luaL_Map", "map", udata);
}

void Manager::registerMe(Script& script, IA* ia)
{
  API::Me* udata = new API::Me(ia);
  script.getVirtualMachine().setClass<API::Me>("luaL_Me", "me", udata);
}

void Manager::registerMap(GameScene* gs)
{
  this->_gs = gs;
}

Manager::Manager(void)
{
}

Manager::~Manager(void)
{
}


