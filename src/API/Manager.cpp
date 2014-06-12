//
// Manager.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Thu Jun  5 10:41:01 2014 raphael defreitas
// Last update Thu Jun 12 20:44:21 2014 raphael defreitas
//

#include	<lua.hpp>

#include	"GameObject.hh"
#include	"Lua/Script.hh"
#include	"Manager.hh"
#include	"Map.hh"
#include	"Me.hh"
#include	"Player.hh"

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
}

void Manager::registerMe(Script& script, IA* ia)
{
  API::Me* udata = new API::Me(ia);
  script.getVirtualMachine().setClass<API::Me>("luaL_Me", "me", udata);
}

Manager::Manager(void)
{
}

Manager::~Manager(void)
{
}


