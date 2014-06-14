//
// Item.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:02:27 2014 raphael defreitas
// Last update Fri Jun 13 23:17:51 2014 raphael defreitas
//

#include	<cstdlib>
#include	<lua.hpp>
#include	<string>

#include	"GameObject.hh"
#include	"object/AGameObject.hh"
#include	"Lua/Script.hh"
#include	"Lua/VirtualMachine.hh"
#include	"Item.hh"

using namespace API;
using namespace Lua;

Item::Item(AGameObject* go) :
  GameObject::GameObject(go)
{
  this->_type = "Item";
}

Item::~Item(void)
{
}

void Item::registerScript(Script& script)
{
  luaL_newmetatable(script.getVirtualMachine().getState(), "luaL_Item");
  Item::registerMethods(script);
  lua_pushvalue(script.getVirtualMachine().getState(), -1);
  lua_setfield(script.getVirtualMachine().getState(), -1, "__index");
  lua_setglobal(script.getVirtualMachine().getState(), "Item");
}

void Item::registerMethods(Script& script)
{
  GameObject::registerMethods(script);
  luaL_Reg methods[] =
    {
      {NULL, NULL}
    };
  luaL_setfuncs(script.getVirtualMachine().getState(), methods, 0);
}
