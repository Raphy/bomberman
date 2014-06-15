//
// BombCapacityBuff.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:02:27 2014 raphael defreitas
// Last update Sun Jun 15 02:03:20 2014 raphael defreitas
//

#include	<cstdlib>
#include	<lua.hpp>
#include	<string>

#include	"Item.hh"
#include	"object/BombCapacityBuff.hh"
#include	"Lua/Script.hh"
#include	"Lua/VirtualMachine.hh"
#include	"BombCapacityBuff.hh"

using namespace API;
using namespace Lua;

API::BombCapacityBuff::BombCapacityBuff(::BombCapacityBuff* buff) :
  Item::Item(buff)
{
  this->_type = "BombCapacityBuff";
}

API::BombCapacityBuff::~BombCapacityBuff(void)
{
}

void API::BombCapacityBuff::registerScript(Script& script)
{
  luaL_newmetatable(script.getVirtualMachine().getState(), "luaL_BombCapacityBuff");
  BombCapacityBuff::registerMethods(script);
  lua_pushvalue(script.getVirtualMachine().getState(), -1);
  lua_setfield(script.getVirtualMachine().getState(), -1, "__index");
  lua_setglobal(script.getVirtualMachine().getState(), "BombCapacityBuff");
}

void API::BombCapacityBuff::registerMethods(Script& script)
{
  Item::registerMethods(script);
  luaL_Reg methods[] =
    {
      {NULL, NULL}
    };
  luaL_setfuncs(script.getVirtualMachine().getState(), methods, 0);
}
