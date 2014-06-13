//
// Wall.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:02:27 2014 raphael defreitas
// Last update Fri Jun 13 21:34:26 2014 raphael defreitas
//

#include	<cstdlib>
#include	<lua.hpp>
#include	<string>

#include	"GameObject.hh"
#include	"object/Wall.hh"
#include	"Lua/Script.hh"
#include	"Lua/VirtualMachine.hh"
#include	"Wall.hh"

using namespace API;
using namespace Lua;

API::Wall::Wall(::Wall* wall) :
  GameObject::GameObject(wall), _wall(wall)
{
  this->_type = "Wall";
}

API::Wall::~Wall(void)
{
}

void API::Wall::registerScript(Script& script)
{
  luaL_newmetatable(script.getVirtualMachine().getState(), "luaL_Wall");
  Wall::registerMethods(script);
  lua_pushvalue(script.getVirtualMachine().getState(), -1);
  lua_setfield(script.getVirtualMachine().getState(), -1, "__index");
  lua_setglobal(script.getVirtualMachine().getState(), "Wall");
}

void API::Wall::registerMethods(Script& script)
{
  GameObject::registerMethods(script);
  luaL_Reg methods[] =
    {
      {NULL, NULL}
    };
  luaL_setfuncs(script.getVirtualMachine().getState(), methods, 0);
}
