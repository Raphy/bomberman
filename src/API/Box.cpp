//
// Box.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:02:27 2014 raphael defreitas
// Last update Fri Jun 13 22:58:32 2014 raphael defreitas
//

#include	<cstdlib>
#include	<lua.hpp>
#include	<string>

#include	"GameObject.hh"
#include	"object/Box.hh"
#include	"Lua/Script.hh"
#include	"Lua/VirtualMachine.hh"
#include	"Box.hh"

using namespace API;
using namespace Lua;

API::Box::Box(::Box* box) :
  GameObject::GameObject(box), _box(box)
{
  this->_type = "Box";
}

API::Box::~Box(void)
{
}

void API::Box::registerScript(Script& script)
{
  luaL_newmetatable(script.getVirtualMachine().getState(), "luaL_Box");
  Box::registerMethods(script);
  lua_pushvalue(script.getVirtualMachine().getState(), -1);
  lua_setfield(script.getVirtualMachine().getState(), -1, "__index");
  lua_setglobal(script.getVirtualMachine().getState(), "Box");
}

void API::Box::registerMethods(Script& script)
{
  GameObject::registerMethods(script);
  luaL_Reg methods[] =
    {
      {NULL, NULL}
    };
  luaL_setfuncs(script.getVirtualMachine().getState(), methods, 0);
}
