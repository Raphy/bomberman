//
// Player.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:02:27 2014 raphael defreitas
// Last update Thu Jun 12 20:25:15 2014 raphael defreitas
//

#include	<cstdlib>
#include	<lua.hpp>
#include	<string>

#include	"GameObject.hh"
#include	"object/IA.hh"
#include	"object/Marvin.hh"
#include	"Lua/Script.hh"
#include	"Lua/VirtualMachine.hh"
#include	"Player.hh"

using namespace API;
using namespace Lua;

Player::Player(Marvin* marvin) :
  GameObject::GameObject(marvin), _marvin(marvin), _ia(NULL)
{
  this->_type = "Player";
}

Player::Player(IA* ia) :
  GameObject::GameObject(ia), _marvin(NULL), _ia(ia)
{
  this->_type = "Player";
}

Player::~Player(void)
{
}

void Player::registerScript(Script& script)
{
  luaL_newmetatable(script.getVirtualMachine().getState(), "luaL_Player");
  Player::registerMethods(script);
  lua_pushvalue(script.getVirtualMachine().getState(), -1);
  lua_setfield(script.getVirtualMachine().getState(), -1, "__index");
  lua_setglobal(script.getVirtualMachine().getState(), "Player");
}

void Player::registerMethods(Script& script)
{
  GameObject::registerMethods(script);
  luaL_Reg methods[] =
    {
      {NULL, NULL}
    };
  luaL_setfuncs(script.getVirtualMachine().getState(), methods, 0);
}
