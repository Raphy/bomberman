//
// Manager.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Thu Jun  5 10:41:01 2014 raphael defreitas
// Last update Sun Jun 15 21:31:38 2014 raphael defreitas
//

#include	<lua.hpp>

#include	"Bomb.hh"
#include	"BombCapacityBuff.hh"
#include	"BombRangeBuff.hh"
#include	"Box.hh"
#include	"Fire.hh"
#include	"game/GameScene.hh"
#include	"GameObject.hh"
#include	"Item.hh"
#include	"Lua/Script.hh"
#include	"Manager.hh"
#include	"Map.hh"
#include	"Me.hh"
#include	"Player.hh"
#include	"SpeedBuff.hh"
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
  API::Box::registerScript(script);
  API::Bomb::registerScript(script);
  API::BombCapacityBuff::registerScript(script);
  API::BombRangeBuff::registerScript(script);
  API::Fire::registerScript(script);
  GameObject::registerScript(script);
  Item::registerScript(script);
  Map::registerScript(script);
  Me::registerScript(script);
  Player::registerScript(script);
  SpeedBuff::registerScript(script);
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


