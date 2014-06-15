//
// Fire.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:02:27 2014 raphael defreitas
// Last update Sun Jun 15 21:31:04 2014 raphael defreitas
//

#include	<cstdlib>
#include	<lua.hpp>
#include	<string>

#include	"GameObject.hh"
#include	"object/Fire.hh"
#include	"Lua/Script.hh"
#include	"Lua/VirtualMachine.hh"
#include	"Fire.hh"

using namespace API;
using namespace Lua;

API::Fire::Fire(::Fire* fire) :
  GameObject::GameObject(fire)
{
  this->_type = "Fire";
}

API::Fire::~Fire(void)
{
}

void API::Fire::registerScript(Script& script)
{
  luaL_newmetatable(script.getVirtualMachine().getState(), "luaL_Fire");
  Fire::registerMethods(script);
  lua_pushvalue(script.getVirtualMachine().getState(), -1);
  lua_setfield(script.getVirtualMachine().getState(), -1, "__index");
  lua_setglobal(script.getVirtualMachine().getState(), "Fire");
}

void API::Fire::registerMethods(Script& script)
{
  GameObject::registerMethods(script);
  luaL_Reg methods[] =
    {
      {NULL, NULL}
    };
  luaL_setfuncs(script.getVirtualMachine().getState(), methods, 0);
}
