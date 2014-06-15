//
// Bomb.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:02:27 2014 raphael defreitas
// Last update Sun Jun 15 21:35:32 2014 raphael defreitas
//

#include	<lua.hpp>
#include	<string>

#include	"Item.hh"
#include	"object/Bomb.hh"
#include	"Lua/Script.hh"
#include	"Lua/VirtualMachine.hh"
#include	"Bomb.hh"

using namespace API;
using namespace Lua;

API::Bomb::Bomb(::Bomb* bomb) :
  Item::Item(bomb), _bomb(bomb)
{
  this->_type = "Bomb";
}

API::Bomb::~Bomb(void)
{
}

double API::Bomb::getTime(void) const
{
  return this->_bomb->getTime();
}

int API::Bomb::getRange(void) const
{
  return this->_bomb->getSteps();
}

void API::Bomb::registerScript(Script& script)
{
  luaL_newmetatable(script.getVirtualMachine().getState(), "luaL_Bomb");
  Bomb::registerMethods(script);
  lua_pushvalue(script.getVirtualMachine().getState(), -1);
  lua_setfield(script.getVirtualMachine().getState(), -1, "__index");
  lua_setglobal(script.getVirtualMachine().getState(), "Bomb");
}

void API::Bomb::registerMethods(Script& script)
{
  Item::registerMethods(script);
  luaL_Reg methods[] =
    {
      {"getTime", API::Bomb::getTime},
      {"getRange", API::Bomb::getRange},
      {NULL, NULL}
    };
  luaL_setfuncs(script.getVirtualMachine().getState(), methods, 0);
}

int API::Bomb::getTime(lua_State* L)
{
  VirtualMachine vm(L);
  API::Bomb* udata = vm.toClass<API::Bomb>();
  lua_pushnumber(L, udata->getTime());
  return 1;
}

int API::Bomb::getRange(lua_State* L)
{
  VirtualMachine vm(L);
  API::Bomb* udata = vm.toClass<API::Bomb>();
  lua_pushnumber(L, udata->getRange());
  return 1;
}
